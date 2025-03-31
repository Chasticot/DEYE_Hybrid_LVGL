lv_obj_t* paramScreen;
lv_obj_t* taWifiSSID;
lv_obj_t* taWifiPass;
lv_obj_t* taDeyeIP;
lv_obj_t* taWeatherLocation;
lv_obj_t* btnSave;
lv_obj_t* btnBack;

void createParametersScreen() {
  paramScreen = lv_obj_create(NULL);
  
  // Titre
  lv_obj_t* title = lv_label_create(paramScreen);
  lv_label_set_text(title, "Paramètres");
  lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
  
  // WiFi
  lv_obj_t* lblWifi = lv_label_create(paramScreen);
  lv_label_set_text(lblWifi, "WiFi");
  lv_obj_align(lblWifi, LV_ALIGN_TOP_LEFT, 20, 60);
  
  taWifiSSID = lv_textarea_create(paramScreen);
  lv_textarea_set_placeholder_text(taWifiSSID, "SSID WiFi");
  lv_obj_set_size(taWifiSSID, 200, 40);
  lv_obj_align(taWifiSSID, LV_ALIGN_TOP_LEFT, 20, 90);
  
  taWifiPass = lv_textarea_create(paramScreen);
  lv_textarea_set_placeholder_text(taWifiPass, "Mot de passe");
  lv_textarea_set_password_mode(taWifiPass, true);
  lv_obj_set_size(taWifiPass, 200, 40);
  lv_obj_align(taWifiPass, LV_ALIGN_TOP_LEFT, 20, 140);
  
  // Deye
  lv_obj_t* lblDeye = lv_label_create(paramScreen);
  lv_label_set_text(lblDeye, "Onduleur Deye");
  lv_obj_align(lblDeye, LV_ALIGN_TOP_LEFT, 20, 200);
  
  taDeyeIP = lv_textarea_create(paramScreen);
  lv_textarea_set_placeholder_text(taDeyeIP, "IP Deye");
  lv_obj_set_size(taDeyeIP, 200, 40);
  lv_obj_align(taDeyeIP, LV_ALIGN_TOP_LEFT, 20, 230);
  
  // Météo
  lv_obj_t* lblWeather = lv_label_create(paramScreen);
  lv_label_set_text(lblWeather, "Météo");
  lv_obj_align(lblWeather, LV_ALIGN_TOP_LEFT, 20, 290);
  
  taWeatherLocation = lv_textarea_create(paramScreen);
  lv_textarea_set_placeholder_text(taWeatherLocation, "Ville,Pays");
  lv_obj_set_size(taWeatherLocation, 200, 40);
  lv_obj_align(taWeatherLocation, LV_ALIGN_TOP_LEFT, 20, 320);
  
  // Boutons
  btnSave = lv_btn_create(paramScreen);
  lv_obj_set_size(btnSave, 120, 50);
  lv_obj_align(btnSave, LV_ALIGN_BOTTOM_LEFT, 20, -20);
  lv_obj_t* lblSave = lv_label_create(btnSave);
  lv_label_set_text(lblSave, "Sauvegarder");
  lv_obj_center(lblSave);
  
  btnBack = lv_btn_create(paramScreen);
  lv_obj_set_size(btnBack, 120, 50);
  lv_obj_align(btnBack, LV_ALIGN_BOTTOM_RIGHT, -20, -20);
  lv_obj_t* lblBack = lv_label_create(btnBack);
  lv_label_set_text(lblBack, "Retour");
  lv_obj_center(lblBack);
  
  lv_obj_add_event_cb(btnSave, saveParameters, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(btnBack, [](lv_event_t* e) {
    lv_scr_load(mainScreen);
  }, LV_EVENT_CLICKED, NULL);
}

void saveParameters(lv_event_t* e) {
  Preferences prefs;
  prefs.begin("DeyeConfig", false);
  
  prefs.putString("ssid", lv_textarea_get_text(taWifiSSID));
  prefs.putString("password", lv_textarea_get_text(taWifiPass));
  prefs.putString("deye_ip", lv_textarea_get_text(taDeyeIP));
  prefs.putString("weather_loc", lv_textarea_get_text(taWeatherLocation));
  
  prefs.end();
  
  // Afficher message confirmation
  lv_obj_t* msg = lv_msgbox_create(NULL, "Info", "Paramètres sauvegardés", NULL, true);
  lv_obj_align(msg, LV_ALIGN_CENTER, 0, 0);
}