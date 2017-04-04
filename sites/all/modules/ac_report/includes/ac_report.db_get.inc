<?
/*
 * Created on Feb 6, 2010
 * Created by Mark Libkuman
 * libkuman@openflows.com
 * www.openflows.com
 * 
 * Created for Manhattan Neighborhood Network
 */


  function ac_report_get_bucket_options() {
    
    $sql = 
      "Select distinct title " .
      "FROM {ac_report_bucket_cache} " .
      "ORDER BY title";
    $result = db_query($sql);
    
    $options['any'] = "Any";
    while ($category = db_fetch_object($result)) {
      $name = $category->title;
      $options[$name] = $name;
    }  
    return $options;
  }
  
  function ac_report_get_facility_options() {
    $sql = 
      "Select distinct facility_name " .
      "FROM {ac_report_item_cache} " .
      "WHERE facility_name is not null and facility_name != ''" .
      "ORDER BY facility_name";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($facility_name = db_fetch_object($result)) {
      $name = $facility_name->facility_name;
      $options[$name] = $name;
    }  
    return $options;
  }
  
  function ac_report_get_inventory_options() {
    $sql = 
      "Select distinct inventory_name " .
      "FROM {ac_report_item_cache} " .
      "WHERE inventory_name is not null " .
      "ORDER BY inventory_name";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($inventory_name = db_fetch_object($result)) {
      $name = $inventory_name->inventory_name;
      $options[$name] = $name;
    }  
    return $options;
  }
  
  function ac_report_get_borough_options() {
    $sql = 
      "Select distinct borough " .
      "FROM {ac_report_producer_cache} " .
      "WHERE borough is not null " .
      "ORDER BY borough";
    $result = db_query($sql);
    //$options['any'] = "Any";
    $options['non_nyc'] = "Non NYC";
    while ($borough = db_fetch_object($result)) {
      $name = $borough->borough;
      $options[$name] = $name;
    }  
    return $options;
  }

  function ac_report_get_runtime_options() {
    $sql = 
      "Select distinct runtime_type " .
      "FROM {ac_report_episode_cache} " .
      "WHERE runtime_type is not null " .
      "ORDER BY runtime_type";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($runtime_type = db_fetch_object($result)) {
      $name = $runtime_type->runtime_type;
      $options[$name] = $name;
    }  
    return $options;
  }
  
  function ac_report_get_schedule_type_options() {
    $sql = 
      "Select distinct schedule_type " .
      "FROM {ac_report_episode_cache} " .
      "WHERE schedule_type is not null " .
      "ORDER BY schedule_type";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($schedule_type = db_fetch_object($result)) {
      $name = $schedule_type->schedule_type;
      $options[$name] = $name;
    }  
    return $options;
  }
  
  function ac_report_get_format_options() {
    $sql = 
      "Select distinct format " .
      "FROM {ac_report_episode_cache} " .
      "WHERE format is not null " .
      "ORDER BY format";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($format = db_fetch_object($result)) {
      $name = $format->format;
      $options[$name] = $name;
    }  
    return $options;
  }
    
  function ac_report_get_live_device_options() {
    $sql = 
      "Select distinct live_device " .
      "FROM {ac_report_episode_cache} " .
      "WHERE live_device is not null " .
      "ORDER BY live_device";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($live_device = db_fetch_object($result)) {
      $name = $live_device->live_device;
      $options[$name] = $name;
    }  
    return $options;
  }
  
  
  function ac_report_get_department_options() {
    $sql = 
      "Select distinct department " .
      "FROM {ac_report_project_cache} " .
      "WHERE department is not null " .
      "ORDER BY department";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($department = db_fetch_object($result)) {
      $name = $department->department;
      $options[$name] = $name;
    }  
    return $options;
  }
  
  
  function ac_report_get_status_options() {
    $sql = 
      "Select distinct status " .
      "FROM {ac_report_producer_class_cache} " .
      "WHERE status is not null " .
      "ORDER BY status";
    $result = db_query($sql);
    //$options['any'] = "Any";
    while ($status = db_fetch_object($result)) {
      $name = $status->status;
      $options[$name] = $name;
    }  
    return $options;
  }
    
  function ac_report_get_certification_options() {
    $sql = 
      "Select distinct certification " .
      "FROM {ac_report_class_cache} " .
      "WHERE certification is not null " .
      "ORDER BY certification";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($certification = db_fetch_object($result)) {
      $name = $certification->certification;
      $options[$name] = $name;
    }  
    return $options;
  }
  function ac_report_get_course_name_options() {
    $sql = 
      "Select distinct course_title " .
      "FROM {ac_report_class_cache} " .
      "WHERE course_title is not null " .
      "ORDER BY course_title";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($course_title = db_fetch_object($result)) {
      $name = $course_title->course_title;
      $options[$name] = $name;
    }  
    return $options;
  }
  function ac_report_get_course_type_options() {
    $sql = 
      "Select distinct course_type " .
      "FROM {ac_report_class_cache} " .
      "WHERE course_type is not null " .
      "ORDER BY course_type";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($course_type = db_fetch_object($result)) {
      $name = $course_type->course_type;
      $options[$name] = $name;
    }  
    return $options;
  }
  
  function ac_report_get_audience_options() {
    $sql = 
      "Select distinct audience " .
      "FROM {ac_report_project_cache} " .
      "WHERE audience is not null " .
      "ORDER BY audience";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($audience = db_fetch_object($result)) {
      $name = $audience->audience;
      $options[$name] = $name;
    }  
    return $options;
  }
  function ac_report_get_interval_options() {
     $sql = 
      "Select distinct `interval` " .
      "FROM {ac_report_project_cache} " .
      "WHERE `interval` is not null " .
      "ORDER BY `interval`";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($interval = db_fetch_object($result)) {
      $name = $interval->interval;
      $options[$name] = $name;
    }  
    return $options;
  }
  function ac_report_get_topic_options() {
    
     $sql = 
      "Select distinct topic " .
      "FROM {ac_report_project_cache} " .
      "WHERE topic is not null " .
      "ORDER BY topic";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($topic = db_fetch_object($result)) {
      $name = $topic->topic;
      $options[$name] = $name;
    }  
    return $options;
  }
  function ac_report_get_language_options() {
   
     $sql = 
      "Select distinct language " .
      "FROM {ac_report_project_cache} " .
      "WHERE language is not null " .
      "ORDER BY language";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($language = db_fetch_object($result)) {
      $name = $language->language;
      $options[$name] = $name;
    }  
    return $options; 
  }
  function ac_report_get_project_status_options() {
   
     $sql = 
      "Select distinct project_status " .
      "FROM {ac_report_project_cache} " .
      "WHERE project_status is not null " .
      "ORDER BY project_status";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($project_status = db_fetch_object($result)) {
      $name = $project_status->project_status;
      $options[$name] = $name;
    }  
    return $options; 
  }
  
  
  function ac_report_get_item_type_options() {
   
     $sql = 
      "Select distinct item_type " .
      "FROM {ac_report_item_cache} " .
      "WHERE item_type is not null " .
      "ORDER BY item_type";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($item_type = db_fetch_object($result)) {
      $name = $item_type->item_type;
      $options[$name] = $name;
    }  
    return $options; 
  }
  
  
  function ac_report_get_facility_code_options() {
   
     $sql = 
      "Select distinct facility_code " .
      "FROM {ac_report_item_cache} " .
      "WHERE facility_code is not null and facility_code != '' " .
      "ORDER BY facility_code";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($facility_code = db_fetch_object($result)) {
      $name = $facility_code->facility_code;
      $options[$name] = $name;
    }  
    return $options; 
  }
  
  
  function ac_report_get_building_options() {
   
     $sql = 
      "Select distinct building " .
      "FROM {ac_report_item_cache} " .
      "WHERE building is not null " .
      "ORDER BY building";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($building = db_fetch_object($result)) {
      $name = $building->building;
      $options[$name] = $name;
    }  
    return $options; 
  }
  
  function ac_report_get_manufacturer_options() {
   
     $sql = 
      "Select distinct manufacturer " .
      "FROM {ac_report_item_cache} " .
      "WHERE manufacturer is not null " .
      "ORDER BY manufacturer";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($manufacturer = db_fetch_object($result)) {
      $name = $manufacturer->manufacturer;
      $options[$name] = $name;
    }  
    return $options; 
  }
   
  function ac_report_get_affiliate_category_options() {
   
     $sql = 
      "Select distinct category " .
      "FROM {ac_report_affiliate_org_category_cache} " .
      "WHERE category is not null " .
      "ORDER BY category";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($category = db_fetch_object($result)) {
      $name = $category->category;
      $options[$name] = $name;
    }  
    return $options; 
  }
  
  function ac_report_get_affiliate_tag_options() {
   
     $sql = 
      "Select distinct tag " .
      "FROM {ac_report_affiliate_org_tag_cache} " .
      "WHERE tag is not null " .
      "ORDER BY tag";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($tag = db_fetch_object($result)) {
      $name = $tag->tag;
      $options[$name] = $name;
    }  
    return $options; 
  }
  
  function ac_report_get_affiliate_group_options() {
   
     $sql = 
      "Select distinct group_name " .
      "FROM {ac_report_affiliate_org_group_cache} " .
      "WHERE group_name is not null " .
      "ORDER BY group_name";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($group = db_fetch_object($result)) {
      $name = $group->group_name;
      $options[$name] = $name;
    }  
    return $options; 
  }
  
  function ac_report_get_producer_group_options() {
   
     $sql = 
      "Select distinct group_name " .
      "FROM {ac_report_producer_group_cache} " .
      "WHERE group_name is not null " .
      "ORDER BY group_name";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($group = db_fetch_object($result)) {
      $name = $group->group_name;
      $options[$name] = $name;
    }  
    return $options; 
  }
  
  function ac_report_get_producer_certifications_options() {
    $sql = 
      "Select distinct certification " .
      "FROM {ac_report_producer_certification_cache} " .
      "WHERE certification is not null " .
      "ORDER BY certification";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($certification = db_fetch_object($result)) {
      $name = $certification->certification;
      $options[$name] = $name;
    }  
    return $options; 
  }
  function ac_report_get_city_council_district_options() {
     $sql = 
      "Select distinct city_council_district " .
      "FROM {ac_report_producer_cache} " .
      "WHERE city_council_district is not null " .
      "ORDER BY city_council_district";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($district = db_fetch_object($result)) {
      $name = $district->city_council_district;
      $options[$name] = $name;
    }  
    return $options; 
  }
  function ac_report_get_verified_options() {
     $sql = 
      "Select distinct verified " .
      "FROM {ac_report_producer_cache} " .
      "WHERE verified is not null " .
      "ORDER BY verified";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($verified = db_fetch_object($result)) {
      $name = $verified->verified;
      $options[$name] = $name;
    }  
    return $options; 
  }
  
  function ac_report_get_bucket_category_options() {
    $sql = 
      "Select distinct bucket_category " .
      "FROM {ac_report_bucket_cache} " .
      "ORDER BY " .
      "bucket_category='DCTV CM Studios' desc, " .
      "bucket_category='DCTV Editing Bays' desc, " .
      "bucket_category='DCTV Facilities' desc, " .
      "bucket_category='Firehouse Studios' desc, " .
      "bucket_category='Firehouse Editing Bays' desc, " .
      "bucket_category='Firehouse Facilities' desc, " .
      
      "bucket_category='59th 3 Camera Studios' desc, " .
      "bucket_category='59th Express Studios' desc, " .
      "bucket_category='59th Editing Bays' desc, " .
      "bucket_category='59th Editing Bays (CM)' desc, " .
      "bucket_category='59th Editing Bays (YC)' desc, " .
      "bucket_category='59th Dubbing/Transfer Stations' desc, " .
      "bucket_category='59th CM Dubbing/Transfer Station' desc, " .

      "bucket_category";
    $result = db_query($sql);
    
    while ($category = db_fetch_object($result)) {
      $name = $category->bucket_category;
      $options[$name] = $name;
    }  
    
    return $options;
  }

 function ac_report_get_item_department_name_options() {
    $sql = 
      "Select distinct department_name " .
      "FROM {ac_report_item_cache} " .
      "WHERE department_name is not null " .
      "ORDER BY department_name";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($inventory_name = db_fetch_object($result)) {
      $name = $inventory_name->department_name;
      $options[$name] = $name;
    }  
    return $options;
  }
  
  function ac_report_get_location_options() {
    $sql = 
      "Select distinct location " .
      "FROM {ac_report_item_cache} " .
      "WHERE location is not null " .
      "AND location != '' " .
      "ORDER BY location";
    $result = db_query($sql);
    $options['any'] = "Any";
    $tmp = array();
    while ($inventory_name = db_fetch_object($result)) {
      $name = $inventory_name->location;
      $tmp[$name] = $name;
    }  
    $extras = array("ES0001-EDIT SUITE A", "ES0004-EDIT SUITE AA", 
      "ES0002-EDIT SUITE B", "ES0005-EDIT SUITE BB", "STU003-STUDIO-EXPRESS");
    foreach($extras as $k=>$extra_name) {
      if (!$tmp[$extra_name]) {
        $tmp[$extra_name] = $extra_name;
      }
    }
    ksort($tmp);
    $options += $tmp;
    
    return $options;
  }
  
  function ac_report_get_item_status_options() {
    $sql = 
      "Select distinct item_status " .
      "FROM {ac_report_item_cache} " .
      "WHERE item_status is not null " .
      "ORDER BY item_status";
    $result = db_query($sql);
    while ($inventory_name = db_fetch_object($result)) {
      $name = $inventory_name->item_status;
      $options[$name] = $name;
    }  
    return $options;
  }
  
  function ac_report_get_primary_trainers() {
    $sql = 
      "SELECT distinct display_name " .
      "FROM {ac_report_producer_cache} p " .
      "INNER JOIN {ac_report_trainer_class_cache} t " .
      "ON t.producer_id=p.producer_id " .
      "ORDER BY display_name ";
    $result = db_query($sql);
    
    $options['any'] = "Any";
    while ($trainer_name = db_fetch_object($result)) {
      $name = $trainer_name->display_name;
      $options[$name] = $name;
    }  
    return $options;
    
  }
  
function ac_report_get_trainer_types() {
  $sql = 
      "SELECT distinct type " .
      "FROM {ac_report_trainer_class_cache}  " .
      "ORDER BY type ";
    $result = db_query($sql);
    
    $options['any'] = "Any";
    while ($trainer = db_fetch_object($result)) {
      $name = $trainer->type;
      $options[$name] = $name;
    }  
    return $options;
}

function ac_report_get_reservation_project_departments() {
  $sql = 
      "SELECT distinct project_department " .
      "FROM {ac_report_reservation_cache}  " .
      "WHERE project_department is not NULL " .
      "ORDER BY project_department ";
    $results = db_query($sql);
    
    $options['any'] = "Any";
    while ($result = db_fetch_object($results)) {
      $name = $result->project_department;
      $options[$name] = $name;
    }  
    return $options;
}

function ac_report_get_premiere_channels() {
    $sql = 
      "Select distinct premiere_channel " .
      "FROM {ac_report_episode_cache} " .
      "WHERE premiere_channel is not null " .
      "ORDER BY premiere_channel";
    $result = db_query($sql);
    $options['any'] = "Any";
    while ($premiere_channel = db_fetch_object($result)) {
      $name = $premiere_channel->premiere_channel;
      $options[$name] = $name;
    }  
    return $options;
  }
  