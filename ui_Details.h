lv_obj_t* detailsScreen;
lv_obj_t* lblMppt1;
lv_obj_t* lblMppt2;
lv_obj_t* btnBack;

void createDetailsScreen() {
  detailsScreen = lv_obj_create(NULL);
  
  // Titre
  lv_obj_t* title = lv_label_create(detailsScreen);
  lv_label_set_text(title, "Détails Production");
  lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
  
  // Données MPPT
  lblMppt1 = lv_label_create(detailsScreen);
  lv_label_set_text(lblMppt1, "MPPT 1: 0.0 kW");
  lv_obj_align(lblMppt1, LV_ALIGN_TOP_MID, 0, 80);
  
  lblMppt2 = lv_label_create(detailsScreen);
  lv_label_set_text(lblMppt2, "MPPT 2: 0.0 kW");
  lv_obj_align(lblMppt2, LV_ALIGN_TOP_MID, 0, 120);
  
  // Bouton retour
  btnBack = lv_btn_create(detailsScreen);
  lv_obj_set_size(btnBack, 120, 50);
  lv_obj_align(btnBack, LV_ALIGN_BOTTOM_MID, 0, -20);
  lv_obj_t* lblBack = lv_label_create(btnBack);
  lv_label_set_text(lblBack, "Retour");
  lv_obj_center(lblBack);
  
  lv_obj_add_event_cb(btnBack, [](lv_event_t* e) {
    lv_scr_load(mainScreen);
  }, LV_EVENT_CLICKED, NULL);
}

void updateDetailsScreen() {
  lv_label_set_text_fmt(lblMppt1, "MPPT 1: %.1f kW", deyeData.mppt1Power);
  lv_label_set_text_fmt(lblMppt2, "MPPT 2: %.1f kW", deyeData.mppt2Power);
}