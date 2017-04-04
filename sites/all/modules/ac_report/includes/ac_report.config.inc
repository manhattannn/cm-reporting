<?
/*
 * Created on Mar 5, 2010
 * Created by Mark Libkuman
 * libkuman@openflows.com
 * www.openflows.com
 * 
 * Created for Manhattan Neighborhood Network
 */

/**
 * THIS FUNCTION FILLS UP ALL THE ARRAYS NECESSARY TO CHANGE THE WAY THE 
 * VIEWS FILTERS APPEAR. ELEMENTS IN THESE ARRAYS WILL BOTH MODIFY TEXT FIELDS 
 * INTO CUSTOMIZED WIDGETS AND ADD EXTRA FILTERS FOR USE IN SUBQUERIES
 * 
 * USE THE EXAMPLE FOR EACH ARRAY. ADDING ELEMENTS TO SOME OF THESE ARRAYS
 * REQUIRES WORK TO BE DONE IN THE ac_report_views_query_subqueries FUNCTION OR
 * ELSE THE VIEWS SUBQUERIES WILL NOT BE ALTERED BY THE NEW FILTERS AS EXPECTED 
 */
 function ac_report_views_filter_alter_form_config($form_id, &$dropdown_fields, 
   &$checkbox_fields, &$date_fields, &$fieldsets, &$additional_date_fields, 
   &$additional_checkboxes,&$additional_dropdowns, &$additional_textfields) {
        
   ////////////////////////////////////////////////////////////
   //DROPDOWNS: THESE TEXTFIELDS WILL BE TURNED INTO DROPDOWNS
   ////////////////////////////////////////////////////////////
   $dropdown_fields = array(
    //'<Filter Identifier>' => '<callback function to get options>'
      'inventory_name'=> 'ac_report_get_inventory_options',
      'facility_name'=> 'ac_report_get_facility_options',
      'bucket_name'=> 'ac_report_get_bucket_options',
      'runtime_type'=> 'ac_report_get_runtime_options',
      'schedule_type'=> 'ac_report_get_schedule_type_options',
      'format'=> 'ac_report_get_format_options',
      'live_device'=> 'ac_report_get_live_device_options',
      'department' => 'ac_report_get_department_options',
      'course_name' => 'ac_report_get_course_name_options',
      'course_type' => 'ac_report_get_course_type_options',
      'certification' => 'ac_report_get_certification_options',
      'audience' => 'ac_report_get_audience_options',
      'interval' => 'ac_report_get_interval_options',
      'topic' => 'ac_report_get_topic_options',
      'language' => 'ac_report_get_language_options',
      'item_type' => 'ac_report_get_item_type_options',
      'facility_code' => 'ac_report_get_facility_code_options',
      'building' => 'ac_report_get_building_options',
      'manufacturer' => 'ac_report_get_manufacturer_options',
      'project_status' => 'ac_report_get_project_status_options',
      'city_council_district' => 'ac_report_get_city_council_district_options',
      'verified' => 'ac_report_get_verified_options',
      'department_name' => 'ac_report_get_item_department_name_options',
      'location' => 'ac_report_get_location_options',
      'primary_trainer_name' => 'ac_report_get_primary_trainers',
      'trainer_type' => 'ac_report_get_trainer_types',
      'project_department' => 'ac_report_get_reservation_project_departments',
      'premiere_channel' => 'ac_report_get_premiere_channels',
    );
    
    
    ////////////////////////////////////////////////////////////
    //CHECKBOXES: THESE TEXTFIELDS WILL BE TURNED INTO CHECKBOXES
    ////////////////////////////////////////////////////////////
    $checkbox_fields = array(
    //'<Filter Identifier>' => '<callback function to get options>'
      'bucket_category' => 'ac_report_get_bucket_category_options',
      'borough'=>'ac_report_get_borough_options',
      'status' => 'ac_report_get_status_options',
      'item_status' => 'ac_report_get_item_status_options',
    );
    
    ////////////////////////////////////////////////////////////
    //DATE FIELDS: THESE TEXTFIELDS WILL BE TURNED INTO DATE WIDGETS
    ////////////////////////////////////////////////////////////
    $date_fields = array(
    //'<Filter Identifier>',
      'reserve_start_time_lower_range',
      'reserve_start_time_upper_range',
      'min_submitted_date',
      'max_submitted_date',
      'min_first_air_date',
      'max_first_air_date',
      'min_last_air_date',
      'max_last_air_date',
      'min_class_start_date',
      'max_class_start_date',
      'project_creation_date_lower_range',
      'project_creation_date_upper_range',
      'affiliate_creation_date_lower_range',
      'affiliate_creation_date_upper_range',
      'min_class_start',
      'max_class_start',
      'min_air_date',
      'max_air_date',
    );
                        
    ////////////////////////////////////////////////////////////
    //FIELDSETS: THESE WILL GROUP AND COLLAPSE EXTRA FILTERS
    ////////////////////////////////////////////////////////////
    if (strpos($form_id, 'views-exposed-form-producer-report-page') === 0){
    //$fieldsets['<Field Name>'] = t('<Field Label>');  
      $fieldsets['producer_extra_filters'] = t("Extra Info");
      $fieldsets['producer_class_filters'] = t("Class Filters");
      $fieldsets['producer_project_filters'] = t("Project Filters");
      $fieldsets['producer_episode_filters'] = t("Episode Filters");
      $fieldsets['producer_reservation_filters'] = t("Reservation Filters");
      $fieldsets['producer_affiliate_filters'] = t("Affiliate Filters");
    }
     else if(strpos($form_id, 'views-exposed-form-project-report-page-1') === 0){
      $fieldsets['project_producer_filters'] = t("Producer Filters (includes Associate Producers)");
      $fieldsets['project_reservation_filters'] = t("Reservation Filters");
      $fieldsets['project_episode_filters'] = t("Episodes Filters");
      $fieldsets['project_affiliate_filters'] = t("Affilates Filters");
     }
     else if (strpos($form_id, 'views-exposed-form-affiliate-report-page-1') === 0) {
      //$fieldsets['<Field Name>'] = t('<Field Label>');  
      $fieldsets['affiliate_org_extra_filters'] = t("Extra Info");
      $fieldsets['affiliate_org_producer_filters'] = t("Producer Filters");
      $fieldsets['affiliate_org_project_filters'] = t("Project Filters");
      $fieldsets['affiliate_org_class_filters'] = t("Class Filters");
      $fieldsets['affiliate_org_episode_filters'] = t("Episode Filters");
      $fieldsets['affiliate_org_reservation_filters'] = t("Reservation Filters");
    }
    else if (strpos($form_id, 'views-exposed-form-producer-classes-report-page') === 0) {
      $fieldsets['producer_class_affiliate_org_filters'] = t("Affiliate Filters");
    }
    else if (strpos($form_id, 'views-exposed-form-item-reservation-report-page') === 0) {
      $fieldsets['item_reservation_affiliate_org_filters'] = t("Affiliate Filters");
    }
    else if (strpos($form_id, 'views-exposed-form-submitted-episodes-report-page') === 0) {
      $fieldsets['episode_affiliate_org_filters'] = t("Affiliate Filters");
    }
    else if (strpos($form_id, 'views-exposed-form-inventory-report-page') === 0) {
    }
    
    ////////////////////////////////////////////////////////////
    //EXTRA DROPDOWNS
    //(Note: adding these requires adding code to the 
    //       ac_report_views_query_subqueries function or else 
    //       the views subqueries will not be altered as expected)
    //    
    //EXAMPLE:
    //$additional_dropdowns['<Field Name>_dropdown'] = 
    //    array('fieldset' => '<Fieldset Name>',
    //           'title' => t('<Field Label>'),
    //           'options' => <Call to function to get options>);
    ////////////////////////////////////////////////////////////  
    if (strpos($form_id, 'views-exposed-form-affiliate-report-page-1') === 0) {
      //EXTRA INFO WIDGETS
      $additional_dropdowns['affiliate_org_category_dropdown'] = 
        array('fieldset' => 'affiliate_org_extra_filters',
               'title' => t('Affiliate Issue Category'), 
               'options' => ac_report_get_affiliate_category_options());
      $additional_dropdowns['affiliate_org_group_dropdown'] = 
        array('fieldset' => 'affiliate_org_extra_filters',
               'title' => t('Affiliate Group Category'), 
               'options' => ac_report_get_affiliate_group_options());
      $additional_dropdowns['affiliate_org_tag_dropdown'] = 
        array('fieldset' => 'affiliate_org_extra_filters',
               'title' => t('Affiliate Tag'), 
               'options' => ac_report_get_affiliate_tag_options());
      //PROJECT WIDGETS
       $additional_dropdowns['project_status_dropdown'] = 
        array('fieldset' => 'affiliate_org_project_filters',
               'title' => t('Project Status'), 
               'options' => ac_report_get_project_status_options());
      $additional_dropdowns['project_schedule_type_dropdown'] = 
        array('fieldset' => 'affiliate_org_project_filters',
               'title' => t('Schedule Type'), 
               'options' => ac_report_get_schedule_type_options());
      $additional_dropdowns['project_format_dropdown'] = 
        array('fieldset' => 'affiliate_org_project_filters',
               'title' => t('Project Format'), 
               'options' => ac_report_get_format_options());
      $additional_dropdowns['project_runtime_type_dropdown'] = 
        array('fieldset' => 'affiliate_org_project_filters',
               'title' => t('Runtime Type'), 
               'options' => ac_report_get_runtime_options());
      $additional_dropdowns['project_department_dropdown'] = 
        array('fieldset' => 'affiliate_org_project_filters',
               'title' => t('Department'), 
               'options' => ac_report_get_department_options());
      $additional_dropdowns['project_live_device_dropdown'] = 
        array('fieldset' => 'affiliate_org_project_filters',
               'title' => t('Live Device'), 
               'options' => ac_report_get_live_device_options());
               
      //CLASS WIDGETS
       $additional_dropdowns['course_name_dropdown'] = 
        array('fieldset' => 'affiliate_org_class_filters',
               'title' => t('Course Name'), 
               'options' => ac_report_get_course_name_options());
      $additional_dropdowns['course_type_dropdown'] = 
        array('fieldset' => 'affiliate_org_class_filters',
               'title' => t('Course Type'), 
               'options' => ac_report_get_course_type_options());
      $additional_dropdowns['certification_dropdown'] = 
        array('fieldset' => 'affiliate_org_class_filters',
               'title' => t('Certification'), 
               'options' => ac_report_get_certification_options());
      $additional_dropdowns['department_dropdown'] = 
        array('fieldset' => 'affiliate_org_class_filters',
               'title' => t('Department'), 
               'options' => ac_report_get_department_options());
               
       //EPISODE WIDGETS
      $additional_dropdowns['runtime_type_dropdown'] = 
        array('fieldset' => 'affiliate_org_episode_filters',
               'title' => t('Runtime Type'), 
               'options' => ac_report_get_runtime_options());
      $additional_dropdowns['schedule_type_dropdown'] = 
        array('fieldset' => 'affiliate_org_episode_filters',
               'title' => t('Schedule Type'), 
               'options' => ac_report_get_schedule_type_options());
      $additional_dropdowns['format_dropdown'] = 
        array('fieldset' => 'affiliate_org_episode_filters',
               'title' => t('Format'), 
               'options' => ac_report_get_format_options());
      $additional_dropdowns['live_device_dropdown'] = 
        array('fieldset' => 'affiliate_org_episode_filters',
               'title' => t('Live Device'), 
               'options' => ac_report_get_live_device_options());
               
      //RESERVATION WIDGETS
      $additional_dropdowns['bucket_name_dropdown'] = 
        array('fieldset' => 'affiliate_org_reservation_filters',
               'title' => t('Bucket Name'), 
               'options' => ac_report_get_bucket_options());
      $additional_dropdowns['facility_name_dropdown'] = 
        array('fieldset' => 'affiliate_org_reservation_filters',
               'title' => t('Facility Name'), 
               'options' => ac_report_get_facility_options());
      $additional_dropdowns['inventory_name_dropdown'] = 
        array('fieldset' => 'affiliate_org_reservation_filters',
               'title' => t('Inventory Name'), 
               'options' => ac_report_get_inventory_options());
               
    }
    
    if (strpos($form_id, 'views-exposed-form-producer-report-page') === 0){
      //EXTRA INFO WIDGETS
      $additional_dropdowns['producer_groups_dropdown'] = 
        array('fieldset' => 'producer_extra_filters',
               'title' => t('Groups'), 
               'options' => ac_report_get_producer_group_options());
      $additional_dropdowns['producer_certifications_dropdown'] = 
        array('fieldset' => 'producer_extra_filters',
               'title' => t('Certifications'), 
               'options' => ac_report_get_producer_certifications_options());
               
      //RESERVATION WIDGETS
      $additional_dropdowns['bucket_name_dropdown'] = 
        array('fieldset' => 'producer_reservation_filters',
               'title' => t('Bucket Name'), 
               'options' => ac_report_get_bucket_options());
      $additional_dropdowns['facility_name_dropdown'] = 
        array('fieldset' => 'producer_reservation_filters',
               'title' => t('Facility Name'), 
               'options' => ac_report_get_facility_options());
      $additional_dropdowns['inventory_name_dropdown'] = 
        array('fieldset' => 'producer_reservation_filters',
               'title' => t('Inventory Name'), 
               'options' => ac_report_get_inventory_options());
    
      //CLASS WIDGETS
       $additional_dropdowns['course_name_dropdown'] = 
        array('fieldset' => 'producer_class_filters',
               'title' => t('Course Name'), 
               'options' => ac_report_get_course_name_options());
      $additional_dropdowns['course_type_dropdown'] = 
        array('fieldset' => 'producer_class_filters',
               'title' => t('Course Type'), 
               'options' => ac_report_get_course_type_options());
      $additional_dropdowns['certification_dropdown'] = 
        array('fieldset' => 'producer_class_filters',
               'title' => t('Certification'), 
               'options' => ac_report_get_certification_options());
      $additional_dropdowns['department_dropdown'] = 
        array('fieldset' => 'producer_class_filters',
               'title' => t('Department'), 
               'options' => ac_report_get_department_options());
       
      //EPISODE WIDGETS
      $additional_dropdowns['runtime_type_dropdown'] = 
        array('fieldset' => 'producer_episode_filters',
               'title' => t('Runtime Type'), 
               'options' => ac_report_get_runtime_options());
      $additional_dropdowns['schedule_type_dropdown'] = 
        array('fieldset' => 'producer_episode_filters',
               'title' => t('Schedule Type'), 
               'options' => ac_report_get_schedule_type_options());
      $additional_dropdowns['format_dropdown'] = 
        array('fieldset' => 'producer_episode_filters',
               'title' => t('Format'), 
               'options' => ac_report_get_format_options());
      $additional_dropdowns['live_device_dropdown'] = 
        array('fieldset' => 'producer_episode_filters',
               'title' => t('Live Device'), 
               'options' => ac_report_get_live_device_options());
      
      //PROJECT WIDGETS
      $additional_dropdowns['project_status_dropdown'] = 
        array('fieldset' => 'producer_project_filters',
               'title' => t('Project Status'), 
               'options' => ac_report_get_project_status_options());
      $additional_dropdowns['project_schedule_type_dropdown'] = 
        array('fieldset' => 'producer_project_filters',
               'title' => t('Schedule Type'), 
               'options' => ac_report_get_schedule_type_options());
      $additional_dropdowns['project_format_dropdown'] = 
        array('fieldset' => 'producer_project_filters',
               'title' => t('Project Format'), 
               'options' => ac_report_get_format_options());
      $additional_dropdowns['project_runtime_type_dropdown'] = 
        array('fieldset' => 'producer_project_filters',
               'title' => t('Runtime Type'), 
               'options' => ac_report_get_runtime_options());
      $additional_dropdowns['project_department_dropdown'] = 
        array('fieldset' => 'producer_project_filters',
               'title' => t('Department'), 
               'options' => ac_report_get_department_options());
      $additional_dropdowns['project_live_device_dropdown'] = 
        array('fieldset' => 'producer_project_filters',
               'title' => t('Live Device'), 
               'options' => ac_report_get_live_device_options());
      
      //AFFILIATE WIDGETS
      $additional_dropdowns['affiliate_category_dropdown'] = 
        array('fieldset' => 'producer_affiliate_filters',
               'title' => t('Affiliate Issue Category'), 
               'options' => ac_report_get_affiliate_category_options());
      $additional_dropdowns['affiliate_group_dropdown'] = 
        array('fieldset' => 'producer_affiliate_filters',
               'title' => t('Affiliate Group Category'), 
               'options' => ac_report_get_affiliate_group_options());
      $additional_dropdowns['affiliate_tag_dropdown'] = 
        array('fieldset' => 'producer_affiliate_filters',
               'title' => t('Affiliate Tag'), 
               'options' => ac_report_get_affiliate_tag_options());
      
    }
    else if(strpos($form_id, 'views-exposed-form-project-report-page-1') === 0){
       //RESERVATION WIDGETS
      $additional_dropdowns['bucket_name_dropdown'] = 
        array('fieldset' => 'project_reservation_filters',
               'title' => t('Bucket Name'), 
               'options' => ac_report_get_bucket_options());
      $additional_dropdowns['facility_name_dropdown'] = 
        array('fieldset' => 'project_reservation_filters',
               'title' => t('Facility Name'), 
               'options' => ac_report_get_facility_options());
      $additional_dropdowns['inventory_name_dropdown'] = 
        array('fieldset' => 'project_reservation_filters',
               'title' => t('Inventory Name'), 
               'options' => ac_report_get_inventory_options());
               
               
      //EPISODE WIDGETS
      $additional_dropdowns['runtime_type_dropdown'] = 
        array('fieldset' => 'project_episode_filters',
               'title' => t('Runtime Type'), 
               'options' => ac_report_get_runtime_options());
      $additional_dropdowns['schedule_type_dropdown'] = 
        array('fieldset' => 'project_episode_filters',
               'title' => t('Schedule Type'), 
               'options' => ac_report_get_schedule_type_options());
      $additional_dropdowns['format_dropdown'] = 
        array('fieldset' => 'project_episode_filters',
               'title' => t('Format'), 
               'options' => ac_report_get_format_options());
      $additional_dropdowns['live_device_dropdown'] = 
        array('fieldset' => 'project_episode_filters',
               'title' => t('Live Device'), 
               'options' => ac_report_get_live_device_options());
               
      //AFFILIATE WIDGETS
      $additional_dropdowns['affiliate_category_dropdown'] = 
        array('fieldset' => 'project_affiliate_filters',
               'title' => t('Affiliate Issue Category'), 
               'options' => ac_report_get_affiliate_category_options());
      $additional_dropdowns['affiliate_group_dropdown'] = 
        array('fieldset' => 'project_affiliate_filters',
               'title' => t('Affiliate Group Category'), 
               'options' => ac_report_get_affiliate_group_options());
      $additional_dropdowns['affiliate_tag_dropdown'] = 
        array('fieldset' => 'project_affiliate_filters',
               'title' => t('Affiliate Tag'), 
               'options' => ac_report_get_affiliate_tag_options());
      
      //PRODUCER WIDGETS
      $additional_dropdowns['producer_groups_dropdown'] = 
        array('fieldset' => 'project_producer_filters',
               'title' => t('Groups'), 
               'options' => ac_report_get_producer_group_options());
      $additional_dropdowns['producer_certifications_dropdown'] = 
        array('fieldset' => 'project_producer_filters',
               'title' => t('Certifications'), 
               'options' => ac_report_get_producer_certifications_options());
      
    }
    else if(strpos($form_id, 'views-exposed-form-producer-classes-report-page') === 0){
      //AFFILIATE WIDGETS
      $additional_dropdowns['affiliate_category_dropdown'] = 
        array('fieldset' => 'producer_class_affiliate_org_filters',
               'title' => t('Affiliate Issue Category'), 
               'options' => ac_report_get_affiliate_category_options());
      $additional_dropdowns['affiliate_group_dropdown'] = 
        array('fieldset' => 'producer_class_affiliate_org_filters',
               'title' => t('Affiliate Group Category'), 
               'options' => ac_report_get_affiliate_group_options());
      $additional_dropdowns['affiliate_tag_dropdown'] = 
        array('fieldset' => 'producer_class_affiliate_org_filters',
               'title' => t('Affiliate Tag'), 
               'options' => ac_report_get_affiliate_tag_options());
    }
    else if (strpos($form_id, 'views-exposed-form-item-reservation-report-page') === 0) {
      //AFFILIATE WIDGETS
      $additional_dropdowns['affiliate_category_dropdown'] = 
        array('fieldset' => 'item_reservation_affiliate_org_filters',
               'title' => t('Affiliate Issue Category'), 
               'options' => ac_report_get_affiliate_category_options());
      $additional_dropdowns['affiliate_group_dropdown'] = 
        array('fieldset' => 'item_reservation_affiliate_org_filters',
               'title' => t('Affiliate Group Category'), 
               'options' => ac_report_get_affiliate_group_options());
      $additional_dropdowns['affiliate_tag_dropdown'] = 
        array('fieldset' => 'item_reservation_affiliate_org_filters',
               'title' => t('Affiliate Tag'), 
               'options' => ac_report_get_affiliate_tag_options());
    }
    else if (strpos($form_id, 'views-exposed-form-submitted-episodes-report-page') === 0) {
      //AFFILIATE WIDGETS
      $additional_dropdowns['affiliate_category_dropdown'] = 
        array('fieldset' => 'episode_affiliate_org_filters',
               'title' => t('Affiliate Issue Category'), 
               'options' => ac_report_get_affiliate_category_options());
      $additional_dropdowns['affiliate_group_dropdown'] = 
        array('fieldset' => 'episode_affiliate_org_filters',
               'title' => t('Affiliate Group Category'), 
               'options' => ac_report_get_affiliate_group_options());
      $additional_dropdowns['affiliate_tag_dropdown'] = 
        array('fieldset' => 'episode_affiliate_org_filters',
               'title' => t('Affiliate Tag'), 
               'options' => ac_report_get_affiliate_tag_options());
    }
    ////////////////////////////////////////////////////////////
    //EXTRA CHECKBOXES
    //(Note: adding these requires adding code to the 
    //       ac_report_views_query_subqueries function or else 
    //       the views subqueries will not be altered as expected)
    //    
    //EXAMPLE:
    //$additional_checkboxes['<Field Name>_checkboxes'] = 
    //    array('fieldset' => '<Fieldset Name>',
    //           'title' => t('<Field Label>'), 
    //           'options' => <Call to function to get options>);
    ////////////////////////////////////////////////////////////
    if (strpos($form_id, 'views-exposed-form-producer-report-page') === 0){
      //CLASS CHECKBOXES
      $additional_checkboxes['class_status_checkboxes'] = 
        array('fieldset' => 'producer_class_filters',
               'title' => t('Class Status'), 
               'options' => ac_report_get_status_options());
      //RESERVATION CHECKBOXES
      $additional_checkboxes['bucket_category_checkboxes'] = 
        array('fieldset' => 'producer_reservation_filters',
               'title' => t('Bucket Category'), 
               'options' => ac_report_get_bucket_category_options());
               //AFFILIATE CHECKBOXES
      $additional_checkboxes['affiliate_borough_checkboxes'] = 
        array('fieldset' => 'producer_affiliate_filters',
               'title' => t('Borough'), 
               'options' => ac_report_get_borough_options());
      
    }
    else if(strpos($form_id, 'views-exposed-form-project-report-page-1') === 0){
      //AFFILIATE CHECKBOXES
      $additional_checkboxes['affiliate_borough_checkboxes'] = 
        array('fieldset' => 'project_affiliate_filters',
               'title' => t('Borough'), 
               'options' => ac_report_get_borough_options());
               
      //RESERVATION CHECKBOXES
      $additional_checkboxes['bucket_category_checkboxes'] = 
        array('fieldset' => 'project_reservation_filters',
               'title' => t('Bucket Category'), 
               'options' => ac_report_get_bucket_category_options());
     
      //PRODUCER CHECKBOXES
      $additional_checkboxes['producer_borough_checkboxes'] = 
        array('fieldset' => 'project_producer_filters',
               'title' => t('Borough'), 
               'options' => ac_report_get_borough_options());
      
    }
    else if (strpos($form_id, 'views-exposed-form-affiliate-report-page-1') === 0) {
      //PRODUCER CHECKBOXES
      $additional_checkboxes['producer_borough_checkboxes'] = 
        array('fieldset' => 'affiliate_org_producer_filters',
               'title' => t('Borough'), 
               'options' => ac_report_get_borough_options());
     //CLASS CHECKBOXES
      $additional_checkboxes['class_status_checkboxes'] = 
        array('fieldset' => 'affiliate_org_class_filters',
               'title' => t('Class Status'), 
               'options' => ac_report_get_status_options());
      //RESERVATION CHECKBOXES
      $additional_checkboxes['bucket_category_checkboxes'] = 
        array('fieldset' => 'affiliate_org_reservation_filters',
               'title' => t('Bucket Category'), 
               'options' => ac_report_get_bucket_category_options());
    }
    else if(strpos($form_id, 'views-exposed-form-producer-classes-report-page') === 0){
      //AFFILIATE CHECKBOXES
      $additional_checkboxes['affiliate_borough_checkboxes'] = 
        array('fieldset' => 'producer_class_affiliate_org_filters',
               'title' => t('Borough'), 
               'options' => ac_report_get_borough_options());               
    }    
    else if (strpos($form_id, 'views-exposed-form-item-reservation-report-page') === 0) {
      //AFFILIATE CHECKBOXES
      $additional_checkboxes['affiliate_borough_checkboxes'] = 
        array('fieldset' => 'item_reservation_affiliate_org_filters',
               'title' => t('Borough'), 
               'options' => ac_report_get_borough_options());
    }  
    else if (strpos($form_id, 'views-exposed-form-submitted-episodes-report-page') === 0) {
      //AFFILIATE CHECKBOXES
      $additional_checkboxes['affiliate_borough_checkboxes'] = 
        array('fieldset' => 'episode_affiliate_org_filters',
               'title' => t('Borough'), 
               'options' => ac_report_get_borough_options());
    }              
    ////////////////////////////////////////////////////////////
    //EXTRA DATE WIDGETS
    //(Note: adding these requires adding code to the 
    //       ac_report_views_query_subqueries function or else 
    //       the views subqueries will not be altered as expected)
    //
    //EXAMPLE: (for both a min date and a max date)
    //$additional_date_fields['<Filter Identifier>_min_date'] = '<Filter Label>';
    //$additional_date_fields['<Filter Identifier>_max_date'] = '<Filter Label>';
    ////////////////////////////////////////////////////////////
    if (strpos($form_id, 'views-exposed-form-producer-report-page') === 0){
      $additional_date_fields['producer_activity_min_date'] = t('Min Activity Date');
      $additional_date_fields['producer_activity_max_date'] = t('Max Activity Date');
    }
    else if(strpos($form_id, 'views-exposed-form-project-report-page-1') === 0){
      $additional_date_fields['project_activity_min_date'] = t('Min Activity Date');
      $additional_date_fields['project_activity_max_date'] = t('Max Activity Date');
    }
    else if(strpos($form_id, 'views-exposed-form-affiliate-report-page-1') === 0){
      $additional_date_fields['affiliate_activity_min_date'] = t('Min Activity Date');
      $additional_date_fields['affiliate_activity_max_date'] = t('Max Activity Date');
    }
     else if (strpos($form_id, 'views-exposed-form-inventory-report-page') === 0) {
       $additional_date_fields['item_reservation_min_date'] = t('Min Reservation Date');
       $additional_date_fields['item_reservation_max_date'] = t('Max Reservation Date');
     }

    ////////////////////////////////////////////////////////////
    //EXTRA TEXTFIELDS 
    //(Note: adding these requires adding code to the 
    //       ac_report_views_query_subqueries function or else 
    //       the views subqueries will not be altered as expected)
    //
    //EXAMPLE:
    //$additional_textfields['<Field Name>_textfield'] = 
    //    array('fieldset' => '<Fieldset Name>',
    //           'title' => '<Field Label>', 
    ////////////////////////////////////////////////////////////    
    if (strpos($form_id, 'views-exposed-form-producer-report-page') === 0){
      //EPISODE WIDGETS
      $additional_textfields['number_of_airings_textfield'] =
        array('fieldset' => 'producer_episode_filters',
               'title' => t('Min Number Of Airings'));
      //PROJECT WIDGETS
      $additional_textfields['project_name_textfield'] =
        array('fieldset' => 'producer_project_filters',
               'title' => t('Project Name'));
      
      //AFFILIATE WIDGETS 
      $additional_textfields['affiliate_org_textfield'] =
        array('fieldset' => 'producer_affiliate_filters',
               'title' => t('Affiliate Org Name'));
    } 
    else if(strpos($form_id, 'views-exposed-form-project-report-page-1') === 0){
      //AFFILIATE WIDGETS 
      $additional_textfields['affiliate_org_textfield'] =
        array('fieldset' => 'project_affiliate_filters',
               'title' => t('Affiliate Org Name'));
      //EPISODE WIDGETS
      $additional_textfields['number_of_airings_textfield'] =
        array('fieldset' => 'project_episode_filters',
               'title' => t('Min Number Of Airings'));
      //PRODUCER WIDGETS 
      $additional_textfields['producer_name_textfield'] =
        array('fieldset' => 'project_producer_filters',
               'title' => t('Producer Name'));
      $additional_textfields['project_zip_textfield'] =
        array('fieldset' => 'project_producer_filters',
               'title' => t('Producer Zip'));
     
    }
    else if(strpos($form_id, 'views-exposed-form-affiliate-report-page-1') === 0){
      //PRODUCER WIDGETS 
      $additional_textfields['producer_name_textfield'] =
        array('fieldset' => 'affiliate_org_producer_filters',
               'title' => t('Producer Name'));
      $additional_textfields['producer_zip_textfield'] =
        array('fieldset' => 'affiliate_org_producer_filters',
               'title' => t('Producer Zip'));
      //EPISODE WIDGETS
      $additional_textfields['number_of_airings_textfield'] =
        array('fieldset' => 'affiliate_org_episode_filters',
               'title' => t('Min Number Of Airings'));
               
      //PROJECT WIDGETS
      $additional_textfields['project_name_textfield'] =
        array('fieldset' => 'affiliate_org_project_filters',
               'title' => t('Project Name'));
    }
    else if(strpos($form_id, 'views-exposed-form-producer-classes-report-page') === 0){
      //AFFILIATE WIDGETS 
      $additional_textfields['affiliate_org_textfield'] =
        array('fieldset' => 'producer_class_affiliate_org_filters',
               'title' => t('Affiliate Org Name'));
      $additional_textfields['affiliate_location_textfield'] =
        array('fieldset' => 'producer_class_affiliate_org_filters',
               'title' => t('Affiliate Location/Facility Location'));
      
    }
    else if (strpos($form_id, 'views-exposed-form-item-reservation-report-page') === 0) {
      //AFFILIATE WIDGETS 
      $additional_textfields['affiliate_org_textfield'] =
        array('fieldset' => 'item_reservation_affiliate_org_filters',
               'title' => t('Affiliate Org Name'));
    }
    else if (strpos($form_id, 'views-exposed-form-submitted-episodes-report-page') === 0) {
      //AFFILIATE WIDGETS 
      $additional_textfields['affiliate_org_textfield'] =
        array('fieldset' => 'episode_affiliate_org_filters',
               'title' => t('Affiliate Org Name'));
    }
 }
 
 /**
  * FILLS ARRAYS THAT ARE USED BY ac_report_views_query_alter(&$view, &$query)
  * THE VALUES IN THESE ARRAYS WILL BE USED TO ALTER THE VIEWS QUERY BY BOTH
  * JOINING SUBQUERIES AS RELATIONSHIPS AND REBUILD THE QUERY WHERE CLAUSE
  * 
  * USE THE EXAMPLE GIVEN FOR EACH ARRAY
  */
 function ac_report_views_query_config($base_table, &$dropdown_ignore_fields, &$checkbox_null_fields,  
      &$checkbox_fields, &$date_popup_fields, &$query_count_transforms){
      
   /////////////////////////////////////////////////////////////////
   //DROPDOWN IGNORE FIELDS
   //ADDING ELEMENTS TO THIS ARRAY ALLOWS A VALUE FROM A ALTERED FILTER 
   //DROPDOWN TO BE IGNORED IN THE QUERY WHERE CLAUSE 
   /////////////////////////////////////////////////////////////////
   $dropdown_ignore_fields = array (
   //'<Full Query Field Name>' => '<Arg To Suppress>',
     'ac_report_bucket_cache_ac_report_item_reservation_cache.title' => 'any',
     'ac_report_bucket_cache_ac_report_item_cache.title'=> 'any',
     'ac_report_item_cache_ac_report_item_reservation_cache.facility_name' => 'any',
     'ac_report_reservation_cache_ac_report_item_reservation_cache.inventory_name' => 'any',
     'ac_report_reservation_cache_ac_report_item_reservation_cache.project_department' => 'any',
     'ac_report_item_cache_ac_report_item_reservation_cache.item_type' => 'any',     

     'ac_report_episode_cache.runtime_type' => 'any',
     'ac_report_episode_cache.schedule_type' => 'any',
     'ac_report_episode_cache.format' => 'any',
     'ac_report_episode_cache.live_device' => 'any',
     'ac_report_project_cache_ac_report_episode_cache.department' => 'any',
     'ac_report_project_cache_ac_report_episode_cache.interval'=> 'any',
     'ac_report_episode_cache.premiere_channel' => 'any',

     'ac_report_class_cache_ac_report_producer_class_cache.course_title' => 'any',
     'ac_report_class_cache_ac_report_producer_class_cache.course_type' => 'any',
     'ac_report_class_cache_ac_report_producer_class_cache.certification' => 'any',
     'ac_report_class_cache_ac_report_producer_class_cache.department' => 'any',
     
     'ac_report_project_cache.project_status'=> 'any',
     'ac_report_project_cache.schedule_type'=> 'any',
     'ac_report_project_cache.format'=> 'any',
     'ac_report_project_cache.audience'=> 'any',
     'ac_report_project_cache.department'=> 'any',
     'ac_report_project_cache.device'=> 'any',
     'ac_report_project_cache.interval'=> 'any',
     'ac_report_project_cache.language'=> 'any',
     'ac_report_project_cache.topic'=> 'any',
     'ac_report_project_cache.runtime'=> 'any',
     'ac_report_project_cache.project_status'=> 'any',
     
     'ac_report_item_cache.item_type'=> 'any',
     'ac_report_item_cache.inventory_name'=> 'any',
     'ac_report_item_cache.facility_code'=> 'any',
     'ac_report_item_cache.building'=> 'any',
     'ac_report_item_cache.manufacturer'=> 'any',
     'ac_report_item_cache.department_name'=> 'any',
     'ac_report_item_cache.location'=> 'any',
     
     
     'ac_report_producer_cache.language'=> 'any',
     'ac_report_producer_cache.verified'=> 'any',
     'ac_report_producer_cache.building'=> 'any',
     'ac_report_producer_cache.city_council_district'=> 'any',
     
     
     'ac_report_affiliate_org_cache.city_council_district'=> 'any',
     
     'ac_report_class_cache.course_title'=> 'any',
     'ac_report_class_cache.department'=> 'any',
     'ac_report_class_cache.primary_trainer_name'=> 'any',
     'ac_report_class_cache.certification'=> 'any',
     'ac_report_class_cache.language'=> 'any',
     
     'ac_report_class_cache_ac_report_trainer_class_cache.department' => 'any',
     'ac_report_trainer_class_cache.type' => 'any',
     'ac_report_class_cache_ac_report_trainer_class_cache.course_title' => 'any',
     'ac_report_class_cache_ac_report_trainer_class_cache.certification' => 'any',
     'ac_report_class_cache_ac_report_trainer_class_cache.course_type' => 'any',
     'ac_report_class_cache_ac_report_trainer_class_cache.language' => 'any',
     'ac_report_class_cache_ac_report_trainer_class_cache.building' => 'any',
     
   );    
      
   /////////////////////////////////////////////////////////////////
   //CHECKBOX FIELDS
   //ADDING ELEMENTS TO THIS ARRAY ALLOWS THE VALUES OF ALTERED FILTER 
   //CHECKBOXES TO BE ADDED TO THE QUERY WHERE CLAUSE 
   /////////////////////////////////////////////////////////////////
   $checkbox_fields = array (
   //'<Full Query Field Name>'=>'<Filter Identifier>'
     'ac_report_bucket_cache_ac_report_item_reservation_cache.bucket_category' => 'bucket_category',
     'ac_report_producer_cache_ac_report_item_reservation_cache.borough' => 'borough',
     'ac_report_producer_cache_ac_report_episode_cache.borough' => 'borough',
     'ac_report_producer_cache_ac_report_producer_class_cache.borough' => 'borough',
     'ac_report_producer_cache.borough' => 'borough',
     'ac_report_affiliate_org_cache.borough' => 'borough',
     'ac_report_producer_class_cache.status' => 'status',
     'ac_report_producer_cache_ac_report_project_cache.borough' => 'borough',
     'ac_report_bucket_cache_ac_report_item_cache.bucket_category' => 'bucket_category',
     'ac_report_item_cache.item_status'=>'item_status'
   );
   
   /////////////////////////////////////////////////////////////////
   //CHECKBOX NULL FIELDS
   //ADDING ELEMENTS TO THIS ARRAY ALLOWS A VALUE FROM A ALTERED FILTER 
   //CHECKBOX TO ACT AS A "is null" IN THE QUERY WHERE CLAUSE 
   /////////////////////////////////////////////////////////////////
   $checkbox_null_fields = array (
   //'<Full Query Field Name>' => '<Arg That Means Look For Null Values>'
     'ac_report_producer_cache_ac_report_item_reservation_cache.borough'=>'non_nyc',
     'ac_report_producer_cache_ac_report_episode_cache.borough'=>'non_nyc',
     'ac_report_producer_cache.borough'=>'non_nyc',
     'ac_report_affiliate_org_cache.borough'=>'non_nyc',
   );
   
   /////////////////////////////////////////////////////////////////
   //DATE POPUP FIELDS
   //ADDING ELEMENTS TO THIS ARRAY ALLOWS THE VALUES OF ALTERED FILTER 
   //DATE WIDGETS TO BE ADDED TO THE QUERY WHERE CLAUSE 
   /////////////////////////////////////////////////////////////////
   $date_popup_fields = array (
   //'<Full Query Field Name>'=>'<Filter Identifiers For Date Ranges>'
     'ac_report_reservation_cache_ac_report_item_reservation_cache.reserve_start_time' =>
       array('upper'=>'reserve_start_time_upper_range',
              'lower'=>'reserve_start_time_lower_range'),
     'ac_report_episode_cache.created' =>
       array('upper'=>'max_submitted_date',
              'lower'=>'min_submitted_date'),
     'ac_report_episode_cache.first_airing_time' =>
       array('upper'=>'max_first_air_date',
              'lower'=>'min_first_air_date'),
     'ac_report_episode_cache.last_airing_time' =>
       array('upper'=>'max_last_air_date',
              'lower'=>'min_last_air_date'),
     'ac_report_project_cache.created' =>
       array('upper'=>'project_creation_date_upper_range',
              'lower'=>'project_creation_date_lower_range'),
     'ac_report_class_cache_ac_report_producer_class_cache.class_start_day' =>
       array('upper'=>'max_class_start_date',
              'lower'=>'max_class_start_date'),
     'ac_report_affiliate_org_cache.creation_date' =>
       array('upper'=>'affiliate_creation_date_upper_range',
              'lower'=>'affiliate_creation_date_lower_range'),
     'ac_report_class_cache.class_start_day' =>
       array('upper'=>'max_class_start',
              'lower'=>'min_class_start'),
     'ac_report_class_cache_ac_report_trainer_class_cache.class_start_day' =>
       array('upper'=>'max_class_start_date',
              'lower'=>'min_class_start_date'),
     'ac_report_airing_cache.start_time' =>
     array('upper'=>'max_air_date',
	   'lower'=>'min_air_date'),

   );
   
    /////////////////////////////////////////////////////////////////
    //QUERY COUNT TRANSFORMS
    //ADD VALUES TO THIS ARRAY TO SWAP THE VALUE FOR A FIELD SO THAT IT
    //USES THE RESULT OF A SUBQUERY RATHER THAN THE VALUE FROM THE TABLES 
    //OF THE VIEW QUERY
    //Note: you must create and join a subquery via the 
    //ac_report_views_query_subqueries(&$query, &$extra_form_values) function  
    /////////////////////////////////////////////////////////////////   
    $query_count_transforms[] = array();    
    //EXAMPLE:
    //$query_count_transforms["<Query Field Name Substring>"] = "<Returned Field From Subquery>";
    if ($base_table == "ac_report_producer_cache" ||
        $base_table == "ac_report_project_cache" ||
        $base_table == "ac_report_affiliate_org_cache") {
      $query_count_transforms["number_of_classes"] = "class_count";
      $query_count_transforms["number_of_episodes"] = "episode_count";
      $query_count_transforms["number_of_projects"] = "project_count";
      $query_count_transforms["number_of_reservations"] = "reservation_count";
      $query_count_transforms["number_of_producers"] = "producer_count";
      $query_count_transforms["number_of_affiliates"] = "affiliate_count";
      if ($base_table == "ac_report_producer_cache" ) {
        $query_count_transforms["number_of_activities"] = 
          "(IF(class_count,       class_count,       0) + " .
          " IF(project_count,     project_count,     0) + " .
          " IF(episode_count,     episode_count,     0) + " .
          " IF(reservation_count, reservation_count, 0))";
      }
      else if ($base_table == "ac_report_project_cache" ) {
        $query_count_transforms["number_of_activities"] = 
          "(IF(episode_count,     episode_count,     0) + " .
          " IF(reservation_count, reservation_count, 0))";
      }
      else if ($base_table == "ac_report_affiliate_org_cache" ) {
        $query_count_transforms["number_of_activities"] = 
          "(IF(class_count,       class_count,       0) + " .
          " IF(episode_count,     episode_count,     0) + " .
          " IF(project_count,     project_count,     0) + " .
          " IF(reservation_count, reservation_count, 0))";
      }
    }
  }
  
  
  /**
   * ADD ELEMENTS TO $subquery_info_array TO BUILD SUBQUERIES THAT 
   * CONDITIONALLY JOIN TO THE VIEWS QUERY
   * 
   * THESE SUBQUERIES ARE TRIGGERED BY THE EXISTENCE OF CERTAIN VIEW FIELDS OR 
   * THE EXISTANCE OF SUBMITTED FORM VALUES FROM THE "EXTRA" FILTERS 
   * 
   * "EXTRA" IN THE CURRENT STATE OF THINGS MEANS THE FIELDS WITHIN THE COLLAPSIBLE 
   * FILTER FIELD SETS
   */  
  function ac_report_views_subquery_config(){
    $subquery_info_array = array();
     //////////////////////////////////////////////////////////////////////////
    //AFFILIATE ORG CONDITIONAL SUBQUERY JOINS
    //////////////////////////////////////////////////////////////////////////
    $subquery_info_array['ac_report_affiliate_org_cache'] = array(
      array(
             'subquery_base_table' =>  'ac_report_affiliate_org_category_cache',
             'subquery_alias' => 'affiliate_org_categories',          
             'subquery_join_field' => 'affiliate_org_id', 
             'subquery_count_field' => 'category_count', 
             'join_type' => 'INNER', 
             'join_type_switch_excludes' => array(
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => "",
                                              'extra_form_value_fields' => array( 
                                                                                        'affiliate_org_category_dropdown',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => '=',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'category', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => 'affiliate_org_category_dropdown', 
                                                  ),                               
                                          ),
             'extra_joins' => array(
                                      ),
            ),
      array(
             'subquery_base_table' =>  'ac_report_affiliate_org_group_cache',
             'subquery_alias' => 'affiliate_org_groups',          
             'subquery_join_field' => 'affiliate_org_id', //the field used to join the views base table to the subquery base table i.e. 'project_id',
             'subquery_count_field' => 'group_count', 
             'join_type' => 'INNER', //how this subquery should be joined, conditional switches from inner to left upon where clause triggers i.e. 'LEFT', 'INNER', or 'conditional'
             'join_type_switch_excludes' => array(
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => "",
                                              'extra_form_value_fields' => array( 
                                                                                        'affiliate_org_group_dropdown',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => '=',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'group_name', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => 'affiliate_org_group_dropdown',  
                                                 ),                               
                                          ),
             'extra_joins' => array(
                                      ),
            ),
      array(
             'subquery_base_table' =>  'ac_report_affiliate_org_tag_cache',
             'subquery_alias' => 'affiliate_org_tags',          
             'subquery_join_field' => 'affiliate_org_id', //the field used to join the views base table to the subquery base table i.e. 'project_id',
             'subquery_count_field' => 'tag_count', 
             'join_type' => 'INNER', //how this subquery should be joined, conditional switches from inner to left upon where clause triggers i.e. 'LEFT', 'INNER', or 'conditional'
             'join_type_switch_excludes' => array(
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => "",
                                              'extra_form_value_fields' => array( 
                                                                                        'affiliate_org_tag_dropdown',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => '=',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'tag', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => 'affiliate_org_tag_dropdown',  
                                                 ),                               
                                          ),
             'extra_joins' => array(
                                      ),
            ),
       
      array(
             'subquery_base_table' =>  'ac_report_producer_affiliate_org_cache',
             'subquery_alias' => 'affiliate_org_producers',          
             'subquery_join_field' => 'affiliate_org_id', //the field used to join the views base table to the subquery base table i.e. 'project_id',
             'subquery_count_field' => 'producer_count', 
             'join_type' => 'conditional', //how this subquery should be joined, conditional switches from inner to left upon where clause triggers i.e. 'LEFT', 'INNER', or 'conditional'
             'join_type_switch_excludes' => array(
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => "ac_report_affiliate_org_cache_number_of_producers",
                                              'extra_form_value_fields' => array( 
                                                                                        'producer_borough_checkboxes',
                                                                                        'producer_name_textfield', 
                                                                                        'producer_zip_textfield',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'producer_id', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => '',  
                                                 ),                               
                                          ),
             'extra_joins' => array(
                                      array(      
                                              'join_table' => 'ac_report_producer_cache', 
                                              'join_field' => 'producer_id', 
                                              'join_triggers' => array( 
                                                                           'producer_borough_checkboxes',
                                                                           'producer_name_textfield',
                                                                           'producer_zip_textfield',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'borough', 
                                                                                        'extra_form_value_field' => 'producer_borough_checkboxes', 
                                                                                       ),                               
                                                                                 array( 
                                                                                        'operator' => 'like',   
                                                                                        'subquery_field' => 'display_name', 
                                                                                        'extra_form_value_field' => 'producer_name_textfield', 
                                                                                       ),      
                                                                                                                     
                                                                                 array( 
                                                                                        'operator' => 'like',   
                                                                                        'subquery_field' => 'zip', 
                                                                                        'extra_form_value_field' => 'producer_zip_textfield', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                      ),
            ),
             array(
             'subquery_base_table' =>  'ac_report_project_affiliate_org_cache',
             'subquery_alias' => 'affiliate_org_projects',          
             'subquery_join_field' => 'affiliate_org_id', 
             'subquery_count_field' => 'project_count', 
             'join_type' => 'conditional', 
             'join_type_switch_excludes' => array(
                                                        'affiliate_activity_min_date',
                                                        'affiliate_activity_max_date',
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => 'ac_report_affiliate_org_cache_number_of_projects',
                                              'extra_form_value_fields' => array( 
                                                                                        'affiliate_activity_min_date',
                                                                                        'affiliate_activity_max_date', 
                                                                                        'project_status_dropdown',
                                                                                        'project_schedule_type_dropdown',
                                                                                        'project_format_dropdown',
                                                                                        'project_runtime_type_dropdown',
                                                                                        'project_department_dropdown',
                                                                                        'project_live_device_dropdown',
                                                                                        'project_name_textfield',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'project_id', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => '',  
                                                 ),                               
                                          ),
             'extra_joins' => array(
                                      array(      
                                              'join_table' => 'ac_report_project_cache', 
                                              'join_field' => 'project_id', 
                                              'join_triggers' => array( 
                                                                           'affiliate_activity_min_date',
                                                                           'affiliate_activity_max_date',
                                                                           'project_status_dropdown',
                                                                           'project_schedule_type_dropdown',
                                                                           'project_format_dropdown',
                                                                           'project_runtime_type_dropdown',
                                                                           'project_department_dropdown',
                                                                           'project_live_device_dropdown',
                                                                           'project_name_textfield',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '>=',   
                                                                                        'subquery_field' => 'created', 
                                                                                        'extra_form_value_field' => 'affiliate_activity_min_date', 
                                                                                       ),         
                                                                                 array( 
                                                                                        'operator' => '<=',   
                                                                                        'subquery_field' => 'created', 
                                                                                        'extra_form_value_field' => 'affiliate_activity_max_date', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'project_status', 
                                                                                        'extra_form_value_field' => 'project_status_dropdown', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'schedule_type', 
                                                                                        'extra_form_value_field' => 'project_schedule_type_dropdown', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'format', 
                                                                                        'extra_form_value_field' => 'project_format_dropdown', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'runtime', 
                                                                                        'extra_form_value_field' => 'project_runtime_type_dropdown', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'department', 
                                                                                        'extra_form_value_field' => 'project_department_dropdown', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'device', 
                                                                                        'extra_form_value_field' => 'project_live_device_dropdown', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => 'like',   
                                                                                        'subquery_field' => 'title', 
                                                                                        'extra_form_value_field' => 'project_name_textfield', 
                                                                                       ),                                          
                                                                                ),           
                                      
                                            ),
                                      ),
            ),
             array(
             'subquery_base_table' =>  'ac_report_project_affiliate_org_cache',
             'subquery_alias' => 'affiliate_org_episodes',          
             'subquery_join_field' => 'affiliate_org_id', 
             'subquery_count_field' => 'episode_count', 
             'join_type' => 'conditional', 
             'join_type_switch_excludes' => array(
                                                        'affiliate_activity_min_date',
                                                        'affiliate_activity_max_date',
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => 'ac_report_affiliate_org_cache_number_of_projects',
                                              'extra_form_value_fields' => array( 
                                                                                        'affiliate_activity_min_date',
                                                                                        'affiliate_activity_max_date', 
                                                                                        'schedule_type_dropdown',
                                                                                        'format_dropdown',
                                                                                        'runtime_type_dropdown',
                                                                                        'live_device_dropdown',
                                                                                        'number_of_airings_textfield',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'project_id', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => '',  
                                                 ),                               
                                          ),
             'extra_joins' => array(
                                      array(      
                                              'join_table' => 'ac_report_episode_cache', 
                                              'join_field' => 'project_id', 
                                              'join_triggers' => array( 
                                                                           'affiliate_activity_min_date',
                                                                           'affiliate_activity_max_date',
                                                                           'schedule_type_dropdown',
                                                                           'format_dropdown',
                                                                           'runtime_type_dropdown',
                                                                           'live_device_dropdown',
                                                                           'number_of_airings_textfield',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '>=',   
                                                                                        'subquery_field' => 'created', 
                                                                                        'extra_form_value_field' => 'affiliate_activity_min_date', 
                                                                                       ),         
                                                                                 array( 
                                                                                        'operator' => '<=',   
                                                                                        'subquery_field' => 'created', 
                                                                                        'extra_form_value_field' => 'affiliate_activity_max_date', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'runtime_type', 
                                                                                        'extra_form_value_field' => 'runtime_type_dropdown', 
                                                                                       ),
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'schedule_type', 
                                                                                        'extra_form_value_field' => 'schedule_type_dropdown', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'format', 
                                                                                        'extra_form_value_field' => 'format_dropdown', 
                                                                                       ),                                                          
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'live_device', 
                                                                                        'extra_form_value_field' => 'live_device_dropdown', 
                                                                                       ),                             
                                                                                 
                                                                                 array( 
                                                                                        'operator' => '>=',   
                                                                                        'subquery_field' => 'number_of_airings', 
                                                                                        'extra_form_value_field' => 'number_of_airings_textfield', 
                                                                                       ),
                                                                                ),           
                                      
                                            ),
                                            
                                      ),
            ),
             array(
             'subquery_base_table' =>  'ac_report_producer_class_cache',
             'subquery_alias' => 'affiliate_org_classes',          
             'subquery_join_field' => 'affiliate_org_id', 
             'subquery_count_field' => 'class_count', 
             'join_type' => 'conditional', 
             'join_type_switch_excludes' => array(
                                                        'affiliate_activity_min_date',
                                                        'affiliate_activity_max_date',
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => 'ac_report_affiliate_org_cache_number_of_classes',
                                              'extra_form_value_fields' => array( 
                                                                                        'affiliate_activity_min_date',
                                                                                        'affiliate_activity_max_date', 
                                                                                        'class_status_checkboxes',
                                                                                        'course_name_dropdown',
                                                                                        'course_type_dropdown',
                                                                                        'certification_dropdown',
                                                                                        'department_dropdown',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null', 
                                                  'subquery_field' => 'affiliate_org_id', 
                                                  'extra_form_value_field' => '',
                                                 ),   
                                           array( 
                                                  'operator' => '=', 
                                                  'subquery_field' => 'status',
                                                  'extra_form_value_field' => 'class_status_checkboxes',  
                                                 ),   
                                          ),
             'extra_joins' => array(
                                      array(      
                                              'join_table' => 'ac_report_class_cache', 
                                              'join_field' => 'class_id', 
                                              'join_triggers' => array( 
                                                                           'affiliate_activity_min_date',
                                                                           'affiliate_activity_max_date',
                                                                           'course_name_dropdown',
                                                                           'course_type_dropdown',
                                                                           'certification_dropdown',
                                                                           'department_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '>=',   
                                                                                        'subquery_field' => 'class_start_day', 
                                                                                        'extra_form_value_field' => 'affiliate_activity_min_date', 
                                                                                       ),         
                                                                                 array( 
                                                                                        'operator' => '<=',   
                                                                                        'subquery_field' => 'class_start_day', 
                                                                                        'extra_form_value_field' => 'affiliate_activity_max_date', 
                                                                                       ),   
                                                                                 array(
                                                                                        'operator' => '=', 
                                                                                        'subquery_field' => 'course_title',
                                                                                        'extra_form_value_field' => 'course_name_dropdown',  
                                                                                       ),
                                                                                 array( 
                                                                                        'operator' => '=', 
                                                                                        'subquery_field' => 'course_type',
                                                                                        'extra_form_value_field' => 'course_type_dropdown',  
                                                                                       ),   
                                                                                 array( 
                                                                                        'operator' => '=', 
                                                                                        'subquery_field' => 'certification',
                                                                                        'extra_form_value_field' => 'certification_dropdown',  
                                                                                       ),   
                                                                                 array( 
                                                                                        'operator' => '=', 
                                                                                        'subquery_field' => 'department',
                                                                                        'extra_form_value_field' => 'department_dropdown',  
                                                                                       ),  
                                                                                ),              
                                            ),
                                      ),
            ),
             
             array(
             'subquery_base_table' =>  'ac_report_item_reservation_cache',
             'subquery_alias' => 'affiliate_org_reservations',          
             'subquery_join_field' => 'affiliate_org_id', 
             'subquery_count_field' => 'reservation_count', 
             'join_type' => 'conditional', 
             'join_type_switch_excludes' => array(
                                                        'affiliate_activity_min_date',
                                                        'affiliate_activity_max_date',
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => 'ac_report_affiliate_org_cache_number_of_classes',
                                              'extra_form_value_fields' => array( 
                                                                                        'affiliate_activity_min_date',
                                                                                        'affiliate_activity_max_date', 
                                                                                        'bucket_name_dropdown',
                                                                                        'facility_name_dropdown',
                                                                                        'inventory_name_dropdown',
                                                                                        'bucket_category_checkboxes',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => '=', 
                                                  'subquery_field' => 'status',
                                                  'extra_form_value_field' => 'class_status_checkboxes',  
                                                 ),   
                                          ),
             'extra_joins' => array(
                                      array(      
                                              'join_table' => 'ac_report_bucket_cache', 
                                              'join_field' => 'bucket_id', 
                                              'join_triggers' => array( 
                                                                           'bucket_name_dropdown',
                                                                           'bucket_category_checkboxes',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'title', 
                                                                                        'extra_form_value_field' => 'bucket_name_dropdown', 
                                                                                       ),         
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'bucket_category', 
                                                                                        'extra_form_value_field' => 'bucket_category_checkboxes', 
                                                                                       ),
                                                                                ),              
                                            ),
                                      array(      
                                              'join_table' => 'ac_report_item_cache', 
                                              'join_field' => 'item_id', 
                                              'join_triggers' => array( 
                                                                           'facility_name_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'facility_name', 
                                                                                        'extra_form_value_field' => 'facility_name_dropdown', 
                                                                                       ),         
                                                                                ),              
                                            ),
                                      array(      
                                              'join_table' => 'ac_report_reservation_cache', 
                                              'join_field' => 'reservation_id', 
                                              'join_triggers' => array( 
                                                                           'inventory_name_dropdown',
                                                                           'affiliate_activity_min_date',
                                                                           'affiliate_activity_max_date',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'inventory_name', 
                                                                                        'extra_form_value_field' => 'inventory_name_dropdown', 
                                                                                       ),
                                                                                 array( 
                                                                                        'operator' => '>=',   
                                                                                        'subquery_field' => 'reserve_start_time', 
                                                                                        'extra_form_value_field' => 'affiliate_activity_min_date', 
                                                                                       ),         
                                                                                 array( 
                                                                                        'operator' => '<=',   
                                                                                        'subquery_field' => 'reserve_start_time', 
                                                                                        'extra_form_value_field' => 'affiliate_activity_max_date', 
                                                                                       ),         
                                                                                       
                                                                                ),              
                                            ),
                                      ),
            ),
    );
    
    
    //////////////////////////////////////////////////////////////////////////
    //PRODUCER CONDITIONAL SUBQUERY JOINS
    //////////////////////////////////////////////////////////////////////////
    $subquery_info_array['ac_report_producer_cache'] = array(
      array(
             'subquery_base_table' =>  'ac_report_producer_group_cache',
             'subquery_alias' => 'producer_groups',          
             'subquery_join_field' => 'producer_id', 
             'subquery_count_field' => 'group_count', 
             'join_type' => 'INNER', 
             'join_type_switch_excludes' => array(
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => NULL, 
                                              'extra_form_value_fields' => array( 
                                                                                        'producer_groups_dropdown',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => '=',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'group_name', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => 'producer_groups_dropdown', //the value to check against in the where clause
                                                  ),                               
                                          ),
             'extra_joins' => array(  
                                      ),
            ),
             array(
             'subquery_base_table' =>  'ac_report_producer_certification_cache',
             'subquery_alias' => 'producer_certifications',          
             'subquery_join_field' => 'producer_id', 
             'subquery_count_field' => 'certification_count', 
             'join_type' => 'INNER', 
             'join_type_switch_excludes' => array(
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => NULL, 
                                              'extra_form_value_fields' => array( 
                                                                                        'producer_certifications_dropdown',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => '=',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'certification', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => 'producer_certifications_dropdown', //the value to check against in the where clause
                                                  ),                               
                                          ),
             'extra_joins' => array(  
                                      ),
            ),
            
             array(
             'subquery_base_table' =>  'ac_report_producer_class_cache',
             'subquery_alias' => 'producer_classes',          
             'subquery_join_field' => 'producer_id', 
             'subquery_count_field' => 'class_count', 
             'join_type' => 'conditional', 
             'join_type_switch_excludes' => array(
                                                        'producer_activity_min_date',
                                                        'producer_activity_max_date',
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => 'ac_report_producer_cache_number_of_classes',
                                              'extra_form_value_fields' => array( 
                                                                                        'producer_activity_min_date',
                                                                                        'producer_activity_max_date', 
                                                                                        'class_status_checkboxes',
                                                                                        'course_name_dropdown',
                                                                                        'course_type_dropdown',
                                                                                        'certification_dropdown',
                                                                                        'department_dropdown',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null', 
                                                  'subquery_field' => 'producer_id', 
                                                  'extra_form_value_field' => '',
                                                 ),   
                                           array( 
                                                  'operator' => '=', 
                                                  'subquery_field' => 'status',
                                                  'extra_form_value_field' => 'class_status_checkboxes',  
                                                 ),   
                                          ),
             'extra_joins' => array(
                                      array(      
                                              'join_table' => 'ac_report_class_cache', 
                                              'join_field' => 'class_id', 
                                              'join_triggers' => array( 
                                                                           'producer_activity_min_date',
                                                                           'producer_activity_max_date',
                                                                           'course_name_dropdown',
                                                                           'course_type_dropdown',
                                                                           'certification_dropdown',
                                                                           'department_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '>=',   
                                                                                        'subquery_field' => 'class_start_day', 
                                                                                        'extra_form_value_field' => 'producer_activity_min_date', 
                                                                                       ),         
                                                                                 array( 
                                                                                        'operator' => '<=',   
                                                                                        'subquery_field' => 'class_start_day', 
                                                                                        'extra_form_value_field' => 'producer_activity_max_date', 
                                                                                       ),   
                                                                                 array(
                                                                                        'operator' => '=', 
                                                                                        'subquery_field' => 'course_title',
                                                                                        'extra_form_value_field' => 'course_name_dropdown',  
                                                                                       ),
                                                                                 array( 
                                                                                        'operator' => '=', 
                                                                                        'subquery_field' => 'course_type',
                                                                                        'extra_form_value_field' => 'course_type_dropdown',  
                                                                                       ),   
                                                                                 array( 
                                                                                        'operator' => '=', 
                                                                                        'subquery_field' => 'certification',
                                                                                        'extra_form_value_field' => 'certification_dropdown',  
                                                                                       ),   
                                                                                 array( 
                                                                                        'operator' => '=', 
                                                                                        'subquery_field' => 'department',
                                                                                        'extra_form_value_field' => 'department_dropdown',  
                                                                                       ),  
                                                                                ),              
                                            ),
                                      ),
            ),
            
             array(
             'subquery_base_table' =>  'ac_report_producer_project_cache',
             'subquery_alias' => 'producer_episodes',          
             'subquery_join_field' => 'producer_id', 
             'subquery_count_field' => 'episode_count', 
             'join_type' => 'conditional', 
             'join_type_switch_excludes' => array(
                                                        'producer_activity_min_date',
                                                        'producer_activity_max_date',
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => 'ac_report_producer_cache_number_of_episodes',
                                              'extra_form_value_fields' => array( 
                                                                                        'producer_activity_min_date',
                                                                                        'producer_activity_max_date', 
                                                                                        'schedule_type_dropdown',
                                                                                        'format_dropdown',
                                                                                        'runtime_type_dropdown',
                                                                                        'live_device_dropdown',
                                                                                        'number_of_airings_textfield',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'producer_id', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => '',  
                                                 ),                               
                                                 
                                           array( 
                                                  'operator' => '=',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'type', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => '',
                                                  'static_value' => 'executive',  
                                                 ),
                                          ),
             'extra_joins' => array(
                                      array(      
                                              'join_table' => 'ac_report_episode_cache', 
                                              'join_field' => 'project_id', 
                                              'join_triggers' => array( 
                                                                           'producer_activity_min_date',
                                                                           'producer_activity_max_date',
                                                                           'schedule_type_dropdown',
                                                                           'format_dropdown',
                                                                           'runtime_type_dropdown',
                                                                           'live_device_dropdown',
                                                                           'number_of_airings_textfield',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '>=',   
                                                                                        'subquery_field' => 'created', 
                                                                                        'extra_form_value_field' => 'producer_activity_min_date', 
                                                                                       ),         
                                                                                 array( 
                                                                                        'operator' => '<=',   
                                                                                        'subquery_field' => 'created', 
                                                                                        'extra_form_value_field' => 'producer_activity_max_date', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'runtime_type', 
                                                                                        'extra_form_value_field' => 'runtime_type_dropdown', 
                                                                                       ),
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'schedule_type', 
                                                                                        'extra_form_value_field' => 'schedule_type_dropdown', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'format', 
                                                                                        'extra_form_value_field' => 'format_dropdown', 
                                                                                       ),                                                          
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'live_device', 
                                                                                        'extra_form_value_field' => 'live_device_dropdown', 
                                                                                       ),                             
                                                                                 
                                                                                 array( 
                                                                                        'operator' => '>=',   
                                                                                        'subquery_field' => 'number_of_airings', 
                                                                                        'extra_form_value_field' => 'number_of_airings_textfield', 
                                                                                       ),
                                                                                ),           
                                      
                                            ),
                                            
                                      ),
            ),
            array(
             'subquery_base_table' =>  'ac_report_producer_project_cache',
             'subquery_alias' => 'producer_projects',          
             'subquery_join_field' => 'producer_id', 
             'subquery_count_field' => 'project_count', 
             'join_type' => 'conditional', 
             'join_type_switch_excludes' => array(
                                                        'producer_activity_min_date',
                                                        'producer_activity_max_date',
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => 'ac_report_producer_cache_number_of_projects',
                                              'extra_form_value_fields' => array( 
                                                                                        'producer_activity_min_date',
                                                                                        'producer_activity_max_date', 
                                                                                        'project_status_dropdown',
                                                                                        'project_schedule_type_dropdown',
                                                                                        'project_format_dropdown',
                                                                                        'project_runtime_type_dropdown',
                                                                                        'project_department_dropdown',
                                                                                        'project_live_device_dropdown',
                                                                                        'project_name_textfield',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'producer_id', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => '',  
                                                 ),                               
                                          ),
             'extra_joins' => array(
                                      array(      
                                              'join_table' => 'ac_report_project_cache', 
                                              'join_field' => 'project_id', 
                                              'join_triggers' => array( 
                                                                           'producer_activity_min_date',
                                                                           'producer_activity_max_date',
                                                                           'project_status_dropdown',
                                                                           'project_schedule_type_dropdown',
                                                                           'project_format_dropdown',
                                                                           'project_runtime_type_dropdown',
                                                                           'project_department_dropdown',
                                                                           'project_live_device_dropdown',
                                                                           'project_name_textfield',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '>=',   
                                                                                        'subquery_field' => 'created', 
                                                                                        'extra_form_value_field' => 'producer_activity_min_date', 
                                                                                       ),         
                                                                                 array( 
                                                                                        'operator' => '<=',   
                                                                                        'subquery_field' => 'created', 
                                                                                        'extra_form_value_field' => 'producer_activity_max_date', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'project_status', 
                                                                                        'extra_form_value_field' => 'project_status_dropdown', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'schedule_type', 
                                                                                        'extra_form_value_field' => 'project_schedule_type_dropdown', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'format', 
                                                                                        'extra_form_value_field' => 'project_format_dropdown', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'runtime', 
                                                                                        'extra_form_value_field' => 'project_runtime_type_dropdown', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'department', 
                                                                                        'extra_form_value_field' => 'project_department_dropdown', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'device', 
                                                                                        'extra_form_value_field' => 'project_live_device_dropdown', 
                                                                                       ),                             
                                                                                 array( 
                                                                                        'operator' => 'like',   
                                                                                        'subquery_field' => 'title', 
                                                                                        'extra_form_value_field' => 'project_name_textfield', 
                                                                                       ),                                          
                                                                                ),           
                                      
                                            ),
                                      ),
            ),
    
      array(
             'subquery_base_table' =>  'ac_report_item_reservation_cache',
             'subquery_alias' => 'producer_reservations',          
             'subquery_join_field' => 'producer_id', 
             'subquery_count_field' => 'reservation_count', 
             'join_type' => 'conditional', 
             'join_type_switch_excludes' => array(
                                                        'producer_activity_min_date',
                                                        'producer_activity_max_date',
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => 'ac_report_producer_cache_number_of_reservations',
                                              'extra_form_value_fields' => array( 
                                                                                        'producer_activity_min_date',
                                                                                        'producer_activity_max_date', 
                                                                                        'bucket_name_dropdown',
                                                                                        'facility_name_dropdown',
                                                                                        'inventory_name_dropdown',
                                                                                        'bucket_category_checkboxes',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'producer_id', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => '',  
                                                 ),                               
                                          ),
             'extra_joins' => array(
                                      array(      
                                              'join_table' => 'ac_report_bucket_cache', 
                                              'join_field' => 'bucket_id', 
                                              'join_triggers' => array( 
                                                                           'bucket_name_dropdown',
                                                                           'bucket_category_checkboxes',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'title', 
                                                                                        'extra_form_value_field' => 'bucket_name_dropdown', 
                                                                                       ),         
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'bucket_category', 
                                                                                        'extra_form_value_field' => 'bucket_category_checkboxes', 
                                                                                       ),
                                                                                ),              
                                            ),
                                      array(      
                                              'join_table' => 'ac_report_item_cache', 
                                              'join_field' => 'item_id', 
                                              'join_triggers' => array( 
                                                                           'facility_name_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'facility_name', 
                                                                                        'extra_form_value_field' => 'facility_name_dropdown', 
                                                                                       ),         
                                                                                ),              
                                            ),
                                      array(      
                                              'join_table' => 'ac_report_reservation_cache', 
                                              'join_field' => 'reservation_id', 
                                              'join_triggers' => array( 
                                                                           'inventory_name_dropdown',
                                                                           'producer_activity_min_date',
                                                                           'producer_activity_max_date',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'inventory_name', 
                                                                                        'extra_form_value_field' => 'inventory_name_dropdown', 
                                                                                       ),
                                                                                 array( 
                                                                                        'operator' => '>=',   
                                                                                        'subquery_field' => 'reserve_start_time', 
                                                                                        'extra_form_value_field' => 'producer_activity_min_date', 
                                                                                       ),         
                                                                                 array( 
                                                                                        'operator' => '<=',   
                                                                                        'subquery_field' => 'reserve_start_time', 
                                                                                        'extra_form_value_field' => 'producer_activity_max_date', 
                                                                                       ),         
                                                                                       
                                                                                ),              
                                            ),
                                      ),
            ),
            array(
             'subquery_base_table' =>  'ac_report_producer_affiliate_org_cache',
             'subquery_alias' => 'producer_affiliates',          
             'subquery_join_field' => 'producer_id', 
             'subquery_count_field' => 'affiliate_count', 
             'join_type' => 'conditional', 
             'join_type_switch_excludes' => array(
                                                        'producer_activity_min_date',
                                                        'producer_activity_max_date',
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => 'ac_report_producer_cache_number_of_affiliates', 
                                              'extra_form_value_fields' => array( 
                                                                                        'producer_activity_min_date',
                                                                                        'producer_activity_max_date', 
                                                                                        'affiliate_category_dropdown',
                                                                                        'affiliate_group_dropdown',
                                                                                        'affiliate_tag_dropdown',
                                                                                        'affiliate_borough_checkboxes',
                                                                                        'affiliate_org_textfield',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'producer_id', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => '', 
                                                  ),                               
                                          ),
             'extra_joins' => array(
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_borough_checkboxes',
                                                                          'affiliate_org_textfield',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => 'like',   
                                                                                        'subquery_field' => 'name', 
                                                                                        'extra_form_value_field' => 'affiliate_org_textfield', 
                                                                                       ),                               
                                                                                       
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'borough', 
                                                                                        'extra_form_value_field' => 'affiliate_borough_checkboxes', 
                                                                                       ),
                                                                                ),
                                      
                                            ),
                                            
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_category_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_category_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'category',
                                                                                        'extra_form_value_field' => 'affiliate_category_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_group_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_group_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'group_name', 
                                                                                        'extra_form_value_field' => 'affiliate_group_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_tag_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_tag_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'tag', 
                                                                                        'extra_form_value_field' => 'affiliate_tag_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                   ),
            ),
    );
    
     //////////////////////////////////////////////////////////////////////////
    //PROJECT CONDITIONAL SUBQUERY JOINS
    //////////////////////////////////////////////////////////////////////////
    $subquery_info_array['ac_report_project_cache' /**the base table of the current view, i.e. 'ac_report_project_cache' */] = array(
      array(
             'subquery_base_table' =>  'ac_report_project_affiliate_org_cache',//the subquery base table that the views base table joins to, i.e. 'ac_report_project_affiliate_org_cache'
             'subquery_alias' => 'project_affiliates',//the alias for the subquery base table, i.e. "project_affiliates"          
             'subquery_join_field' => 'project_id', //the field used to join the views base table to the subquery base table i.e. 'project_id',
             'subquery_count_field' => 'affiliate_count', //the alias of the count of the subquery, either used in a views field or a views header, i.e. 'affiliate_count'
             'join_type' => 'conditional', //how this subquery should be joined, conditional switches from inner to left upon where clause triggers i.e. 'LEFT', 'INNER', or 'conditional'
             'join_type_switch_excludes' => array(
                                                        'project_activity_min_date',
                                                        'project_activity_max_date',
                                                       ),
             
           'subquery_triggers' => array( 
                                              'query_field' => 'ac_report_project_cache_number_of_affiliates', 
                                              'extra_form_value_fields' => array( 
                                                                                        'project_activity_min_date',
                                                                                        'project_activity_max_date', 
                                                                                        'affiliate_category_dropdown',
                                                                                        'affiliate_group_dropdown',
                                                                                        'affiliate_tag_dropdown',
                                                                                        'affiliate_borough_checkboxes',
                                                                                        'affiliate_org_textfield',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'project_id', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => '', 
                                                  ),                               
                                          ),
             'extra_joins' => array(
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_borough_checkboxes',
                                                                          'affiliate_org_textfield',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => 'like',   
                                                                                        'subquery_field' => 'name', 
                                                                                        'extra_form_value_field' => 'affiliate_org_textfield', 
                                                                                       ),                               
                                                                                       
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'borough', 
                                                                                        'extra_form_value_field' => 'affiliate_borough_checkboxes', 
                                                                                       ),
                                                                                ),
                                      
                                            ),
                                            
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_category_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_category_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'category',
                                                                                        'extra_form_value_field' => 'affiliate_category_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_group_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_group_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'group_name', 
                                                                                        'extra_form_value_field' => 'affiliate_group_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_tag_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_tag_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'tag', 
                                                                                        'extra_form_value_field' => 'affiliate_tag_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                    ),
           ),
      array(
             'subquery_base_table' =>  'ac_report_item_reservation_cache',
             'subquery_alias' => 'project_reservations',          
             'subquery_join_field' => 'project_id', 
             'subquery_count_field' => 'reservation_count', 
             'join_type' => 'conditional', 
             'join_type_switch_excludes' => array(
                                                        'project_activity_min_date',
                                                        'project_activity_max_date',
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => 'ac_report_project_cache_number_of_reservations',
                                              'extra_form_value_fields' => array( 
                                                                                        'project_activity_min_date',
                                                                                        'project_activity_max_date', 
                                                                                        'bucket_name_dropdown',
                                                                                        'facility_name_dropdown',
                                                                                        'inventory_name_dropdown',
                                                                                        'bucket_category_checkboxes',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'project_id', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => '',  
                                                 ),                               
                                          ),
             'extra_joins' => array(
                                      array(      
                                              'join_table' => 'ac_report_bucket_cache', 
                                              'join_field' => 'bucket_id', 
                                              'join_triggers' => array( 
                                                                           'bucket_name_dropdown',
                                                                           'bucket_category_checkboxes',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'title', 
                                                                                        'extra_form_value_field' => 'bucket_name_dropdown', 
                                                                                       ),         
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'bucket_category', 
                                                                                        'extra_form_value_field' => 'bucket_category_checkboxes', 
                                                                                       ),
                                                                                ),              
                                            ),
                                      array(      
                                              'join_table' => 'ac_report_item_cache', 
                                              'join_field' => 'item_id', 
                                              'join_triggers' => array( 
                                                                           'facility_name_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'facility_name', 
                                                                                        'extra_form_value_field' => 'facility_name_dropdown', 
                                                                                       ),         
                                                                                ),              
                                            ),
                                      array(      
                                              'join_table' => 'ac_report_reservation_cache', 
                                              'join_field' => 'reservation_id', 
                                              'join_triggers' => array( 
                                                                           'inventory_name_dropdown',
                                                                           'project_activity_min_date',
                                                                           'project_activity_max_date',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'inventory_name', 
                                                                                        'extra_form_value_field' => 'inventory_name_dropdown', 
                                                                                       ),
                                                                                 array( 
                                                                                        'operator' => '>=',   
                                                                                        'subquery_field' => 'reserve_start_time', 
                                                                                        'extra_form_value_field' => 'project_activity_min_date', 
                                                                                       ),         
                                                                                 array( 
                                                                                        'operator' => '<=',   
                                                                                        'subquery_field' => 'reserve_start_time', 
                                                                                        'extra_form_value_field' => 'project_activity_max_date', 
                                                                                       ),         
                                                                                       
                                                                                ),              
                                            ),
                                      ),
            ),
      array(
             'subquery_base_table' =>  'ac_report_episode_cache',
             'subquery_alias' => 'project_episodes',          
             'subquery_join_field' => 'project_id', 
             'subquery_count_field' => 'episode_count', 
             'join_type' => 'conditional', 
             'join_type_switch_excludes' => array(
                                                        'project_activity_min_date',
                                                        'project_activity_max_date',
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => 'ac_report_project_cache_number_of_episodes',
                                              'extra_form_value_fields' => array( 
                                                                                        'project_activity_min_date',
                                                                                        'project_activity_max_date', 
                                                                                        'schedule_type_dropdown',
                                                                                        'format_dropdown',
                                                                                        'runtime_type_dropdown',
                                                                                        'live_device_dropdown',
                                                                                        'number_of_airings_textfield',
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                            array( 
                                                  'operator' => 'is not null',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'project_id', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => '',  
                                                 ),                              
                                            array( 
                                              'operator' => '=',   
                                              'subquery_field' => 'runtime_type', 
                                              'extra_form_value_field' => 'runtime_type_dropdown', 
                                            ),
                                            array( 
                                              'operator' => '=',   
                                              'subquery_field' => 'schedule_type', 
                                              'extra_form_value_field' => 'schedule_type_dropdown', 
                                            ),                             
                                            array( 
                                              'operator' => '=',   
                                              'subquery_field' => 'format', 
                                              'extra_form_value_field' => 'format_dropdown', 
                                            ),                                                          
                                            array( 
                                              'operator' => '=',   
                                              'subquery_field' => 'live_device', 
                                              'extra_form_value_field' => 'live_device_dropdown', 
                                            ),                             
                                            array( 
                                              'operator' => '>=',   
                                              'subquery_field' => 'number_of_airings', 
                                             'extra_form_value_field' => 'number_of_airings_textfield', 
                                            ),                           
                                            array( 
                                              'operator' => '>=',   
                                              'subquery_field' => 'created', 
                                             'extra_form_value_field' => 'project_activity_min_date', 
                                            ),                           
                                            array( 
                                              'operator' => '<=',   
                                              'subquery_field' => 'created', 
                                             'extra_form_value_field' => 'project_activity_max_date', 
                                            ), 
                                          ),
             'extra_joins' => array(
                                                                                
                                      ),
            ),
     array(
             'subquery_base_table' =>  'ac_report_producer_project_cache',
             'subquery_alias' => 'project_producers',          
             'subquery_join_field' => 'project_id', //the field used to join the views base table to the subquery base table i.e. 'project_id',
             'subquery_count_field' => 'total_producer_count', 
             'join_type' => 'conditional', //how this subquery should be joined, conditional switches from inner to left upon where clause triggers i.e. 'LEFT', 'INNER', or 'conditional'
             'join_type_switch_excludes' => array(
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => "",
                                              'extra_form_value_fields' => array( 
                                                                                        'producer_borough_checkboxes',
                                                                                        'producer_name_textfield', 
                                                                                        'producer_zip_textfield', 
                                                                                        'producer_groups_dropdown', 
                                                                                        'producer_certification_dropdown',
                                                                                       ),
                                              // 'always_join' => TRUE,
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'project_id', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => '',  
                                                 ),                               
                                          ),
             'extra_joins' => array(
                                      array(      
                                              'join_table' => 'ac_report_producer_cache', 
                                              'join_field' => 'producer_id', 
                                              'join_triggers' => array( 
                                                                           'producer_borough_checkboxes',
                                                                           'producer_name_textfield',
                                                                           'producer_zip_textfield',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'borough', 
                                                                                        'extra_form_value_field' => 'producer_borough_checkboxes', 
                                                                                       ),                               
                                                                                 array( 
                                                                                        'operator' => 'like',   
                                                                                        'subquery_field' => 'display_name', 
                                                                                        'extra_form_value_field' => 'producer_name_textfield', 
                                                                                       ),      
                                                                                                                     
                                                                                 array( 
                                                                                        'operator' => 'like',   
                                                                                        'subquery_field' => 'zip', 
                                                                                        'extra_form_value_field' => 'producer_zip_textfield', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                      array(      
                                              'join_table' => 'ac_report_producer_certification_cache', 
                                              'join_field' => 'producer_id', 
                                              'join_triggers' => array( 
                                                                           'producer_certifications_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'certification', 
                                                                                        'extra_form_value_field' => 'producer_certifications_dropdown', 
                                                                                       ),                                                              
                                                                                ),
                                      
                                            ),
                                      array(      
                                              'join_table' => 'ac_report_producer_group_cache', 
                                              'join_field' => 'producer_id', 
                                              'join_triggers' => array( 
                                                                           'producer_groups_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'group_name', 
                                                                                        'extra_form_value_field' => 'producer_groups_dropdown', 
                                                                                       ),                                                              
                                                                                ),
                                      
                                            ),
                                      ),
            ),      
    );
     //////////////////////////////////////////////////////////////////////////
    //PRODUCER CLASS CONDITIONAL SUBQUERY JOINS
    //////////////////////////////////////////////////////////////////////////
    $subquery_info_array['ac_report_producer_class_cache' /**the base table of the current view, i.e. 'ac_report_project_cache' */] = array(
      array(
             'subquery_base_table' =>  'ac_report_affiliate_org_cache',//the subquery base table that the views base table joins to, i.e. 'ac_report_project_affiliate_org_cache'
             'subquery_alias' => 'producer_class_affiliates',//the alias for the subquery base table, i.e. "project_affiliates"          
             'subquery_join_field' => 'affiliate_org_id', //the field used to join the views base table to the subquery base table i.e. 'project_id',
             'subquery_count_field' => 'affiliate_count', //the alias of the count of the subquery, either used in a views field or a views header, i.e. 'affiliate_count'
             'join_type' => 'INNER', //how this subquery should be joined, conditional switches from inner to left upon where clause triggers i.e. 'LEFT', 'INNER', or 'conditional'
             'join_type_switch_excludes' => array(
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => '', //a views field that's existence triggers the subquery joining, i.e. ac_report_project_cache_number_of_episodes
                                              'extra_form_value_fields' => array( 
                                                                                      'affiliate_category_dropdown',
                                                                                      'affiliate_group_dropdown',
                                                                                      'affiliate_tag_dropdown',
                                                                                      'affiliate_borough_checkboxes',
                                                                                      'affiliate_org_textfield',
                                                                                        '',//a extra form value that a non null value triggers the subquery, i.e. affiliate_borough_checkboxes
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null',   
                                                  'subquery_field' => 'affiliate_org_id', 
                                                  'extra_form_value_field' => '', 
                                                 ),
                               
                                           array( 
                                                  'operator' => 'like',   
                                                  'subquery_field' => 'name', 
                                                  'extra_form_value_field' => 'affiliate_org_textfield',
                                                 ),   
                               
                                           array( 
                                                 'operator' => '=',   
                                                 'subquery_field' => 'borough', 
                                                 'extra_form_value_field' => 'affiliate_borough_checkboxes', 
                                                ),
                                          ),
             'extra_joins' => array(
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_category_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_category_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'category',
                                                                                        'extra_form_value_field' => 'affiliate_category_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_group_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_group_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'group_name', 
                                                                                        'extra_form_value_field' => 'affiliate_group_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_tag_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_tag_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'tag', 
                                                                                        'extra_form_value_field' => 'affiliate_tag_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                   ),
            ),
            
      array(
             'subquery_base_table' =>  'ac_report_class_cache',//the subquery base table that the views base table joins to, i.e. 'ac_report_project_affiliate_org_cache'
             'subquery_alias' => 'producer_class_classes',//the alias for the subquery base table, i.e. "project_affiliates"          
             'subquery_join_field' => 'class_id', //the field used to join the views base table to the subquery base table i.e. 'project_id',
             'subquery_count_field' => 'class_count', //the alias of the count of the subquery, either used in a views field or a views header, i.e. 'affiliate_count'
             'join_type' => 'INNER', //how this subquery should be joined, conditional switches from inner to left upon where clause triggers i.e. 'LEFT', 'INNER', or 'conditional'
             'join_type_switch_excludes' => array(
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => '', //a views field that's existence triggers the subquery joining, i.e. ac_report_project_cache_number_of_episodes
                                              'extra_form_value_fields' => array( 
                                                                                      'affiliate_location_textfield',
                                                                                        '',//a extra form value that a non null value triggers the subquery, i.e. affiliate_borough_checkboxes
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           
                                           array( 
                                                  'operator' => 'like',   
                                                  'subquery_field' => 'affiliate_location', 
                                                  'extra_form_value_field' => 'affiliate_location_textfield', 
                                                 ),                               
                                           
                                          ),
              'extra_joins' => array(),

            )
    );
     //////////////////////////////////////////////////////////////////////////
    //ITEM RESERVATION CONDITIONAL SUBQUERY JOINS
    //////////////////////////////////////////////////////////////////////////
    $subquery_info_array['ac_report_item_reservation_cache' /**the base table of the current view, i.e. 'ac_report_project_cache' */] = array(
      array(
             'subquery_base_table' =>  'ac_report_affiliate_org_cache',//the subquery base table that the views base table joins to, i.e. 'ac_report_project_affiliate_org_cache'
             'subquery_alias' => 'item_reservation_affiliates',//the alias for the subquery base table, i.e. "project_affiliates"          
             'subquery_join_field' => 'affiliate_org_id', //the field used to join the views base table to the subquery base table i.e. 'project_id',
             'subquery_count_field' => 'affiliate_count', //the alias of the count of the subquery, either used in a views field or a views header, i.e. 'affiliate_count'
             'join_type' => 'INNER', //how this subquery should be joined, conditional switches from inner to left upon where clause triggers i.e. 'LEFT', 'INNER', or 'conditional'
             'join_type_switch_excludes' => array(
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => '', //a views field that's existence triggers the subquery joining, i.e. ac_report_project_cache_number_of_episodes
                                              'extra_form_value_fields' => array( 
                                                                                      'affiliate_category_dropdown',
                                                                                      'affiliate_group_dropdown',
                                                                                      'affiliate_tag_dropdown',
                                                                                      'affiliate_borough_checkboxes',
                                                                                      'affiliate_org_textfield',
                                                                                        '',//a extra form value that a non null value triggers the subquery, i.e. affiliate_borough_checkboxes
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null',   
                                                  'subquery_field' => 'affiliate_org_id', 
                                                  'extra_form_value_field' => '', 
                                                 ),                               
                                           
                                           array( 
                                                  'operator' => 'like',   
                                                  'subquery_field' => 'name', 
                                                  'extra_form_value_field' => 'affiliate_org_textfield', 
                                                 ),                               
                                                                                       
                                           array( 
                                                 'operator' => '=',   
                                                 'subquery_field' => 'borough', 
                                                 'extra_form_value_field' => 'affiliate_borough_checkboxes', 
                                                ),
                                          ),
             'extra_joins' => array(
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_category_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_category_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'category',
                                                                                        'extra_form_value_field' => 'affiliate_category_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_group_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_group_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'group_name', 
                                                                                        'extra_form_value_field' => 'affiliate_group_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_tag_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_tag_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'tag', 
                                                                                        'extra_form_value_field' => 'affiliate_tag_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                   ),
            ),
    );
    
     //////////////////////////////////////////////////////////////////////////
    //EPISODE CONDITIONAL SUBQUERY JOINS
    //////////////////////////////////////////////////////////////////////////
    $subquery_info_array['ac_report_episode_cache' /**the base table of the current view, i.e. 'ac_report_project_cache' */] = array(
      array(
             'subquery_base_table' =>  'ac_report_project_affiliate_org_cache',//the subquery base table that the views base table joins to, i.e. 'ac_report_project_affiliate_org_cache'
             'subquery_alias' => 'episode_affiliates',//the alias for the subquery base table, i.e. "project_affiliates"          
             'subquery_join_field' => 'project_id', //the field used to join the views base table to the subquery base table i.e. 'project_id',
             'subquery_count_field' => 'affiliate_count', //the alias of the count of the subquery, either used in a views field or a views header, i.e. 'affiliate_count'
             'join_type' => 'INNER', //how this subquery should be joined, conditional switches from inner to left upon where clause triggers i.e. 'LEFT', 'INNER', or 'conditional'
             'join_type_switch_excludes' => array(
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => '', //a views field that's existence triggers the subquery joining, i.e. ac_report_project_cache_number_of_episodes
                                              'extra_form_value_fields' => array( 
                                                                                      'affiliate_category_dropdown',
                                                                                      'affiliate_group_dropdown',
                                                                                      'affiliate_tag_dropdown',
                                                                                      'affiliate_borough_checkboxes',
                                                                                      'affiliate_org_textfield',
                                                                                        '',//a extra form value that a non null value triggers the subquery, i.e. affiliate_borough_checkboxes
                                                                                       ),
                                             ),
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null',   
                                                  'subquery_field' => 'project_id', 
                                                  'extra_form_value_field' => '', 
                                                 ),                               
                                           
                                          ),
             'extra_joins' => array(
             
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_borough_checkboxes',
                                                                          'affiliate_org_textfield',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => 'like',   
                                                                                        'subquery_field' => 'name', 
                                                                                        'extra_form_value_field' => 'affiliate_org_textfield', 
                                                                                       ),                               
                                                                                       
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'borough', 
                                                                                        'extra_form_value_field' => 'affiliate_borough_checkboxes', 
                                                                                       ),
                                                                                ),
                                      
                                            ),
                                      
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_category_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_category_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'category',
                                                                                        'extra_form_value_field' => 'affiliate_category_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_group_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_group_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'group_name', 
                                                                                        'extra_form_value_field' => 'affiliate_group_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                       array(      
                                              'join_table' => 'ac_report_affiliate_org_tag_cache', 
                                              'join_field' => 'affiliate_org_id', 
                                              'join_triggers' => array( 
                                                                          'affiliate_tag_dropdown',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '=',   
                                                                                        'subquery_field' => 'tag', 
                                                                                        'extra_form_value_field' => 'affiliate_tag_dropdown', 
                                                                                       ),                               
                                                                                ),
                                      
                                            ),
                                   ),
            ),
    );
    
    //////////////////////////////////////////////////////////////////////////
    //INVENTORY CONDITIONAL SUBQUERY JOINS
    //////////////////////////////////////////////////////////////////////////
    $subquery_info_array['ac_report_item_cache' /**the base table of the current view, i.e. 'ac_report_project_cache' */] = array(
      array(
             'subquery_base_table' =>  'ac_report_item_reservation_cache',
             'subquery_alias' => 'item_reservations',          
             'subquery_join_field' => 'item_id', 
             'subquery_count_field' => 'reservation_count', 
             'join_type' => 'conditional', 
             'join_type_switch_excludes' => array(
                                                       ),
             'subquery_triggers' => array( 
                                              'query_field' => '',
                                              'extra_form_value_fields' => array( 
                                                                                        'item_reservation_min_date',
                                                                                        'item_reservation_max_date',
                                                                                       ),
                                              'always_join' => TRUE,       
                                             ),
                                             
             'subquery_where' =>  array(
                                           array( 
                                                  'operator' => 'is not null',  //should be '=', '>=', '<=', 'is null', 'is not null'
                                                  'subquery_field' => 'item_id', //the name of subquery field, i.e. 'affiliate_org_id'
                                                  'extra_form_value_field' => '',  
                                                 ),                    
                                                            
                                          ),
             'extra_joins' => array(
                                      array(      
                                              'join_table' => 'ac_report_reservation_cache', 
                                              'join_field' => 'reservation_id', 
                                              'join_triggers' => array( 
                                                                           'item_reservation_min_date',
                                                                           'item_reservation_max_date',
                                                                          ),
                                               'join_where_clauses' => array(
                                                                                 array( 
                                                                                        'operator' => '>=',   
                                                                                        'subquery_field' => 'reserve_start_time', 
                                                                                        'extra_form_value_field' => 'item_reservation_min_date', 
                                                                                       ),         
                                                                                 array( 
                                                                                        'operator' => '<=',   
                                                                                        'subquery_field' => 'reserve_start_time', 
                                                                                        'extra_form_value_field' => 'item_reservation_max_date', 
                                                                                       ),         
                                                                                       
                                                                                ),              
                                            ),
                                      ),
            ),
      );
    return $subquery_info_array;
  } 
  