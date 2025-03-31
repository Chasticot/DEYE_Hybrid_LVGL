lv_obj_t* mainScreen;
lv_obj_t* lblTime;
lv_obj_t* lblDate;
lv_obj_t* lblWeather;
lv_obj_t* lblGridPower;
lv_obj_t* lblPvPower;
lv_obj_t* lblBatterySOC;
lv_obj_t* lblBatteryPower;
lv_obj_t* lblDailyProduction;
lv_obj_t* lblDailyConsumption;
lv_obj_t* lblDailyGridConsumption;
lv_obj_t* btnTempoToday;
lv_obj_t* btnTempoTomorrow;
lv_obj_t* btnDetails;

void createMainScreen() {
  mainScreen = lv_obj_create(NULL);
  
  // Header avec date/heure et météo
  lv_obj_t* header = lv_obj_create(mainScreen);
  lv_obj_set_size(header, 480, 60);
  
  lblTime = lv_label_create(header);
  lv_obj_align(lblTime, LV_ALIGN_LEFT_MID, 10, 0);
  
  lblDate = lv_label_create(header);
  lv_obj_align(lblDate, LV_ALIGN_LEFT_MID, 10, 20);
  
  lblWeather = lv_label_create(header);
  lv_obj_align(lblWeather, LV_ALIGN_RIGHT_MID, -10, 0);
  
  // Section puissance instantanée
  lv_obj_t* powerSection = lv_obj_create(mainScreen);
  lv_obj_set_size(powerSection, 480, 120);
  lv_obj_align(powerSection, LV_ALIGN_TOP_MID, 0, 60);
  
  lblGridPower = lv_label_create(powerSection);
  lv_label_set_text(lblGridPower, "Réseau: 0.0 kW");
  lv_obj_align(lblGridPower, LV_ALIGN_LEFT_MID, 20, -20);
  
  lblPvPower = lv_label_create(powerSection);
  lv_label_set_text(lblPvPower, "PV: 0.0 kW");
  lv_obj_align(lblPvPower, LV_ALIGN_LEFT_MID, 20, 20);
  
  // Section batterie
  lv_obj_t* batterySection = lv_obj_create(mainScreen);
  lv_obj_set_size(batterySection, 480, 100);
  lv_obj_align(batterySection, LV_ALIGN_TOP_MID, 0, 180);
  
  lblBatterySOC = lv_label_create(batterySection);
  lv_label_set_text(lblBatterySOC, "Batterie: 0%");
  lv_obj_align(lblBatterySOC, LV_ALIGN_LEFT_MID, 20, -20);
  
  lblBatteryPower = lv_label_create(batterySection);
  lv_label_set_text(lblBatteryPower, "Puissance: 0.0 kW");
  lv_obj_align(lblBatteryPower, LV_ALIGN_LEFT_MID, 20, 20);
  
  // Section consommation journalière
  lv_obj_t* dailySection = lv_obj_create(mainScreen);
  lv_obj_set_size(dailySection, 480, 120);
  lv_obj_align(dailySection, LV_ALIGN_TOP_MID, 0, 280);
  
  lblDailyProduction = lv_label_create(dailySection);
  lv_label_set_text(lblDailyProduction, "Prod: 0.0 kWh");
  lv_obj_align(lblDailyProduction, LV_ALIGN_LEFT_MID, 20, -40);
  
  lblDailyConsumption = lv_label_create(dailySection);
  lv_label_set_text(lblDailyConsumption, "Conso: 0.0 kWh");
  lv_obj_align(lblDailyConsumption, LV_ALIGN_LEFT_MID, 20, 0);
  
  lblDailyGridConsumption = lv_label_create(dailySection);
  lv_label_set_text(lblDailyGridConsumption, "Réseau: 0.0 kWh");
  lv_obj_align(lblDailyGridConsumption, LV_ALIGN_LEFT_MID, 20, 40);
  
  // Boutons Tempo
  btnTempoToday = lv_btn_create(mainScreen);
  lv_obj_set_size(btnTempoToday, 80, 80);
  lv_obj_align(btnTempoToday, LV_ALIGN_BOTTOM_LEFT, 20, -20);
  
  btnTempoTomorrow = lv_btn_create(mainScreen);
  lv_obj_set_size(btnTempoTomorrow, 80, 80);
  lv_obj_align(btnTempoTomorrow, LV_ALIGN_BOTTOM_RIGHT, -20, -20);
  
  // Bouton détails
  btnDetails = lv_btn_create(mainScreen);
  lv_obj_set_size(btnDetails, 120, 50);
  lv_obj_align(btnDetails, LV_ALIGN_BOTTOM_MID, 0, -20);
  lv_obj_t* lblDetails = lv_label_create(btnDetails);
  lv_label_set_text(lblDetails, "Détails");
  lv_obj_center(lblDetails);
  
  lv_obj_add_event_cb(btnDetails, [](lv_event_t* e) {
    lv_scr_load(detailsScreen);
  }, LV_EVENT_CLICKED, NULL);
}

void updateMainScreen() {
  // Mise à jour date/heure
  timeClient.update();
  lv_label_set_text(lblTime, timeClient.getFormattedTime().c_str());
  
  // Mise à jour données Deye
  lv_label_set_text_fmt(lblGridPower, "Réseau: %.1f kW", deyeData.gridPower);
  lv_label_set_text_fmt(lblPvPower, "PV: %.1f kW", deyeData.pvPower);
  lv_label_set_text_fmt(lblBatterySOC, "Batterie: %d%%", (int)deyeData.batterySOC);
  lv_label_set_text_fmt(lblBatteryPower, "Puissance: %.1f kW", deyeData.batteryPower);
  lv_label_set_text_fmt(lblDailyProduction, "Prod: %.1f kWh", deyeData.dailyProduction);
  lv_label_set_text_fmt(lblDailyConsumption, "Conso: %.1f kWh", deyeData.dailyConsumption);
  lv_label_set_text_fmt(lblDailyGridConsumption, "Réseau: %.1f kWh", deyeData.dailyGridConsumption);
  
  // Mise à jour météo
  lv_label_set_text(lblWeather, weatherInfo.c_str());
  
  // Mise à jour Tempo
  updateTempoDisplay();
}

void updateTempoDisplay() {
  // Couleur aujourd'hui
  lv_obj_set_style_bg_color(btnTempoToday, getTempoColor(tempoColorToday), 0);
  lv_obj_t* lblToday = lv_label_create(btnTempoToday);
  lv_label_set_text_fmt(lblToday, "%d", tempoDayToday);
  lv_obj_center(lblToday);
  
  // Couleur demain
  lv_obj_set_style_bg_color(btnTempoTomorrow, getTempoColor(tempoColorTomorrow), 0);
  lv_obj_t* lblTomorrow = lv_label_create(btnTempoTomorrow);
  lv_label_set_text_fmt(lblTomorrow, "%d", tempoDayTomorrow);
  lv_obj_center(lblTomorrow);
}

lv_color_t getTempoColor(String color) {
  if (color == "blue") return lv_palette_main(LV_PALETTE_BLUE);
  if (color == "white") return lv_color_white();
  if (color == "red") return lv_palette_main(LV_PALETTE_RED);
  return lv_color_black();
}