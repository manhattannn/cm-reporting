<?
/*
 * Created on Feb 2, 2010
 * Created by Mark Libkuman
 * libkuman@openflows.com
 * www.openflows.com
 * 
 * Created for Manhattan Neighborhood Network
 */



function ac_report_recreate_cache_tables() {
  ac_report_recreate_reservation_cache('ac_report_reservation_cache');
  ac_report_recreate_item_reservation_cache('ac_report_item_reservation_cache');  
  ac_report_recreate_bucket_cache('ac_report_bucket_cache');
  ac_report_recreate_item_cache('ac_report_item_cache');
  ac_report_recreate_course_cache('ac_report_course_cache');
  ac_report_recreate_class_cache('ac_report_class_cache');
  ac_report_recreate_session_cache('ac_report_session_cache');
  ac_report_recreate_trainer_class_cache('ac_report_trainer_class_cache');
  ac_report_recreate_trainer_session_cache('ac_report_trainer_session_cache');
  ac_report_recreate_producer_class_cache('ac_report_producer_class_cache');
  ac_report_recreate_producer_session_cache('ac_report_producer_session_cache');
  ac_report_recreate_producer_certification_cache('ac_report_producer_certification_cache');
  ac_report_recreate_producer_cache('ac_report_producer_cache');
  ac_report_recreate_producer_group_cache('ac_report_producer_group_cache');
  ac_report_recreate_producer_project_cache('ac_report_producer_project_cache');
  ac_report_recreate_producer_affiliate_org_cache('ac_report_producer_affiliate_org_cache');
  ac_report_recreate_project_cache('ac_report_project_cache');
  ac_report_recreate_project_affiliate_org_cache('ac_report_project_affiliate_org_cache');
  ac_report_recreate_episode_cache('ac_report_episode_cache');
  ac_report_recreate_airing_cache('ac_report_airing_cache');
  ac_report_recreate_affiliate_org_cache('ac_report_affiliate_org_cache');
  ac_report_recreate_affiliate_org_tag_cache('ac_report_affiliate_org_tag_cache');
  ac_report_recreate_affiliate_org_group_cache('ac_report_affiliate_org_group_cache');
  ac_report_recreate_affiliate_org_verification_cache('ac_report_affiliate_org_verification_cache');
  ac_report_recreate_affiliate_org_category_cache('ac_report_affiliate_org_category_cache');	
  ac_report_recreate_project_author_cache('ac_report_project_author_cache');
  ac_report_recreate_table_indexes();
}

function ac_report_recreate_project_author_cache($table_name) {
$sql = "
  DROP TABLE IF EXISTS $table_name;
 ";
 db_query($sql);
 
 $sql = "
  CREATE TABLE $table_name (
    project_author_id     int(11)   NOT NULL AUTO_INCREMENT,
    producer_id        int(11)     , 
    project_id         int(11)     , 
    producer_name     varchar(60) , 
    PRIMARY KEY  (project_author_id) 
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
 ";
  db_query($sql);  
}

function ac_report_recreate_reservation_cache($table_name) {
 $sql = "
  DROP TABLE IF EXISTS $table_name;
 ";
 db_query($sql);
 
 $sql = "
  CREATE TABLE $table_name (
    reservation_id     int(11)     , 
    producer_id        int(10)     , 
    project_id         int(11)     , 
    reserve_start_time timestamp   DEFAULT '0000-00-00 00:00:00', 
    reserve_end_time   timestamp   DEFAULT '0000-00-00 00:00:00', 
    inventory_name     varchar(50) , 
    type               varchar(50) , 
    deleted            tinyint(1)  , 
    affiliate_org_id   int(11)     , 
    note               text        , 
    reserve_start_int  int(11)     , 
    reserve_end_int    int(11)     , 
    reserve_length     int(11)     ,
    project_department varchar(50),
    PRIMARY KEY  (reservation_id) 
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
 ";
  db_query($sql);  
}



function ac_report_recreate_item_reservation_cache($table_name) {
 $sql = "
  DROP TABLE IF EXISTS $table_name;
 ";
 db_query($sql);
 
 $sql = "
  CREATE TABLE $table_name (
    item_reservation_id int(11) NOT NULL,
    bucket_reservation_id int(11)  , 
    bucket_id             varchar(32)  , 
    reservation_id        int(11)  , 
    item_id               int(11)     , 
    producer_id           int(10)     , 
    project_id            int(11)     , 
    affiliate_org_id      int(11)     , 
    check_out_time        timestamp  DEFAULT '0000-00-00 00:00:00',  
    check_in_time         timestamp  DEFAULT '0000-00-00 00:00:00', 
    check_out_time_int    int(11)     , 
    check_in_time_int     int(11)     , 
    check_out_duration    int(11)     , 
    note                  text        ,
    item_condition        varchar(30) ,
    PRIMARY KEY  (item_reservation_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
 ";
  db_query($sql);  
}


  
function ac_report_recreate_bucket_cache($table_name) {
 $sql = "
  DROP TABLE IF EXISTS $table_name;
 ";
 db_query($sql);
 
 $sql = "
  CREATE TABLE $table_name (
 bucket_id varchar(32),
 title varchar(128) NOT NULL,
 created timestamp  DEFAULT '0000-00-00 00:00:00', 
 changed timestamp  DEFAULT '0000-00-00 00:00:00', 
 bucket_type longtext,
 price  float,
 bucket_category varchar(255),
 inventory_name varchar(255),
 certification varchar(255),   
 budget_multiplier varchar(255),
  PRIMARY KEY  (bucket_id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}


function ac_report_recreate_item_cache($table_name) {
  $sql = "
  DROP TABLE IF EXISTS $table_name;
 ";
 db_query($sql);
 
 $sql = "
  CREATE TABLE $table_name (
  item_id int(10)                     ,
  title   varchar(128) NOT NULL       ,
  facility_name varchar(128)          ,
  created timestamp  DEFAULT '0000-00-00 00:00:00', 
  changed timestamp  DEFAULT '0000-00-00 00:00:00', 
  item_type varchar(48)               ,
  bucket_id varchar(32)                   ,
  facility_code longtext              ,
  price  float                        , 
  warranty_expiration_date varchar(20), 
  warranty_expiration_date_int int(11),
  serial_number longtext              , 
  model longtext                      ,  
  inventory_number longtext           , 
  production_code longtext            ,
  in_service_date varchar(20)         ,
  in_service_date_int int(11)         , 
  location varchar(255)               , 
  location_item_id int(11)           , 
  building varchar(255)               ,
  item_status varchar(255)            ,
  inventory_name varchar(255)         ,
  department_name varchar(255)         ,
  manufacturer varchar(255)           ,
  gl_account_code varchar(255)        ,
  equipment_category varchar(255)     ,
  accessories longtext                ,
  description longtext                ,  
  PRIMARY KEY  (item_id)              
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}


function  ac_report_recreate_course_cache($table_name) {
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
 $sql = "
  CREATE TABLE $table_name (
  course_id int(10),
  title varchar(128) NOT NULL,
  created int(11),
  changed int(11), 
  prereq_course_id int(10),
  certification varchar(255),
  course_type varchar(255),
  PRIMARY KEY  (course_id)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
 }
 
function ac_report_recreate_class_cache($table_name) {
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
 $sql = "
  CREATE TABLE $table_name (
  class_id int(10)  NOT NULL AUTO_INCREMENT,
  event_id int(10),
  legacy_class_id int(10),
  title varchar(128) NOT NULL,
  created timestamp   DEFAULT '0000-00-00 00:00:00', 
  changed timestamp   DEFAULT '0000-00-00 00:00:00', 
  course_id int(11)     , 
  primary_trainer_name varchar(255)     , 
  course_title varchar(128),
  certification varchar(255),
  course_type varchar(255),
  number_of_sessions int(11), 
  capacity int(11), 
  affiliate_org_id int(11), 
  affiliate_org_name varchar(255), 
  number_attended int(11),
  number_producer_students int(11),
  language varchar(255),
  building varchar(255),
  department varchar(255),
  class_start_day timestamp   DEFAULT '0000-00-00 00:00:00', 
  session_hours int(11), 
  student_list longtext,
  affiliate_location longtext,  

  PRIMARY KEY  (class_id)         
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}

function ac_report_recreate_session_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
  $sql = "
  CREATE TABLE $table_name (
  session_id int(10),
  title varchar(128) NOT NULL,
  created int(11),
  changed int(11), 
  class_id int(11), 
  reservation_id int(11), 
  location_item_id int(11), 
  location_affiliate_org_id int(11), 
  PRIMARY KEY  (session_id)        
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}

function ac_report_recreate_producer_class_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
 db_query($sql);
 
 $sql = "
  CREATE TABLE $table_name (
  class_producer_id int(10) NOT NULL AUTO_INCREMENT,
  participant_id int(10),
  class_id int(10),
  producer_id int(10),
  contact_id int(11),
  affiliate_org_id int(11), 
  status varchar(30),
  PRIMARY KEY  (class_producer_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}

function ac_report_recreate_producer_session_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
  $sql = "
  CREATE TABLE $table_name (
  session_producer_id int(10),
  session_id int(10),
  producer_id int(10),
  status varchar(30),
  PRIMARY KEY  (session_producer_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}

function ac_report_recreate_trainer_class_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
  $sql = "
  CREATE TABLE $table_name (
  trainer_class_id int(10) NOT NULL AUTO_INCREMENT,
  class_id int(10),
  producer_id int(10),
  type varchar(24),
  PRIMARY KEY  (trainer_class_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  }

function ac_report_recreate_trainer_session_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
  $sql = "
  CREATE TABLE $table_name (
  trainer_session_id int(10) NOT NULL AUTO_INCREMENT,
  session_id int(10),
  producer_id int(10),
  type varchar(24),
  PRIMARY KEY  (trainer_session_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}

function ac_report_recreate_producer_certification_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
  $sql = "
  CREATE TABLE $table_name (
  producer_certification_id int(10) NOT NULL AUTO_INCREMENT,
  producer_id int(10),
  certification varchar(255),
  PRIMARY KEY  (producer_certification_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}

function ac_report_recreate_producer_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
  $sql = "
  CREATE TABLE $table_name (
  producer_id int(10),
  username varchar(60),
  email varchar(64),
  created int(11),
  display_name varchar(128), 
  phone_primary varchar(64), 
  phone_other varchar(64), 
  street_address varchar(288), 
  city varchar(288), 
  state varchar(288), 
  zip varchar(24), 
  borough varchar(48), 
  verification_date timestamp DEFAULT '0000-00-00 00:00:00',
  verified varchar(255),
  city_council_district varchar(128),
  language varchar(255),
  building varchar(255),
  number_of_classes int(11),
  number_of_episodes int(11),
  number_of_projects int(11),
  number_of_reservations int(11),
  number_of_affiliates int(11),
  number_of_activities int(11),
  PRIMARY KEY  (producer_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}

function ac_report_recreate_producer_group_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
  $sql = "
  CREATE TABLE $table_name (
  producer_group_id int(10) NOT NULL AUTO_INCREMENT,
  producer_id int(10),
  group_name varchar(128),
  PRIMARY KEY  (producer_group_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}
function ac_report_recreate_project_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
  $sql = "
  CREATE TABLE $table_name (
  project_id int(10),
  node_id int(10),   
  title varchar(128) NOT NULL,
  created timestamp    DEFAULT '0000-00-00 00:00:00',
  changed timestamp    DEFAULT '0000-00-00 00:00:00',
  exec_producer_id int(11),  
  narrative longtext,   
  public_contact_info longtext , 
  public_url longtext, 
  public_email_value longtext, 
  project_status varchar(255),
  `interval` varchar(255),
  language varchar(255),
  department varchar(255),
  audience varchar(255),
  content_type varchar(255),
  format varchar(255),
  topic varchar(255),
  schedule_type varchar(255),
  device varchar(255),
  runtime varchar(255),
  verification_date int(11),
  deactivation_date varchar(255),
  msn varchar(255),
  number_of_episodes int(11),
  number_of_reservations int(11),
  number_of_affiliates int(11),
  number_of_producers int(11),
  number_of_activities int(11),
  PRIMARY KEY  (project_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}
function ac_report_recreate_producer_project_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
  $sql = "
  CREATE TABLE $table_name (
  producer_project_id int(10) NOT NULL AUTO_INCREMENT,
  producer_id int(10),
  project_id int(10),
  type varchar(24),
  PRIMARY KEY  (producer_project_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}

function ac_report_recreate_episode_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
  //FIXME: ADD MORE CHECKIN/CHECKOUT AND REJECT INFORMATION
  //NOT NECESSARY FOR REPORTING BUT WOULD BE NECESSARY IN MIGRATION
  $sql = "
  CREATE TABLE $table_name (
  episode_id int(10),
  episode_number int(10),
  project_id int(10),
  exec_producer_id int(10),
  associate_producer_name   varchar(255),  
  special_producer_email   varchar(255),  
  special_producer_website   varchar(255),  
  special_producer_address   varchar(255),   
  special_producer_phone   varchar(255),  
  title varchar(128) NOT NULL,
  narrative longtext,
  notes longtext,
  created timestamp   DEFAULT '0000-00-00 00:00:00',
  changed timestamp   DEFAULT '0000-00-00 00:00:00',
  duration int(11),
  time_code_in int(11),
  time_code_out int(11),
  timing_duration int(11),
  transcoded_time_code_in int(11),
  transcoded_time_code_out int(11),
  runtime_type varchar(255),
  language varchar(255),
  audience varchar(255),
  content_type varchar(255),
  format varchar(255),
  topic varchar(255),
  schedule_type varchar(255),
  live_device varchar(255),
  reject_reason varchar(255),
  delivered_via varchar(255),
  first_airing_time timestamp   DEFAULT '0000-00-00 00:00:00',
  last_airing_time timestamp   DEFAULT '0000-00-00 00:00:00',
  number_of_airings int(10) default 0, 
  premiere_channel varchar(255),
  PRIMARY KEY (`episode_id`),
  KEY `ep_prod_producer_id` (`exec_producer_id`),
  KEY `ep_proj_project_id` (`project_id`)
  ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}

function ac_report_recreate_airing_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
  $sql = "
  CREATE TABLE $table_name (
  airing_id int(10),
  episode_id int(10),
  project_id int(10),    
  title varchar(128) NOT NULL,
  created timestamp   DEFAULT '0000-00-00 00:00:00',
  changed timestamp   DEFAULT '0000-00-00 00:00:00',
  duration int(10), 
  start_time timestamp   DEFAULT '0000-00-00 00:00:00', 
  end_time timestamp   DEFAULT '0000-00-00 00:00:00',
  airing_status varchar(255),
  airing_type varchar(255),
  channel varchar(255),
  PRIMARY KEY (`airing_id`),
  KEY `start_time` (`start_time`),
  KEY `episode_start_time` (`episode_id`,`start_time`),
  KEY `episode_id` (`episode_id`),
  KEY `airing_id` (`airing_id`)
  ) ENGINE=InnoDB DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}

function ac_report_recreate_affiliate_org_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
  $sql = " 
  CREATE TABLE $table_name (
  affiliate_org_id int(10),
  name varchar(128),
  website varchar(255),
  email varchar(64),
  phone_primary varchar(64), 
  phone_other varchar(64), 
  fax varchar(64), 
  street_address varchar(255), 
  city varchar(64), 
  state varchar(64), 
  zip varchar(24), 
  borough varchar(48), 
  city_council_district varchar(128),
  creation_date timestamp DEFAULT '0000-00-00 00:00:00',
  number_of_projects int(11),
  number_of_producers int(11),
  number_of_episodes int(11),
  number_of_reservations int(11),
  number_of_classes int(11),
  number_of_activities int(11),
  PRIMARY KEY  (affiliate_org_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}

function ac_report_recreate_producer_affiliate_org_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
  $sql = "
  CREATE TABLE $table_name (
  producer_affiliate_id int(10) NOT NULL AUTO_INCREMENT,
  affiliate_org_id int(10),
  producer_id int(10),
  PRIMARY KEY  (producer_affiliate_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}


function ac_report_recreate_project_affiliate_org_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
 
  $sql = "
  CREATE TABLE $table_name (
  project_affiliate_id int(10) NOT NULL AUTO_INCREMENT,
  affiliate_org_id int(10),
  project_id int(10),
  PRIMARY KEY  (project_affiliate_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}


function ac_report_recreate_affiliate_org_tag_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
  $sql = "
  CREATE TABLE $table_name (
  affiliate_org_tag_id int(10) NOT NULL AUTO_INCREMENT,
  affiliate_org_id int(10),
  tag varchar(128),
  PRIMARY KEY  (affiliate_org_tag_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}



function ac_report_recreate_affiliate_org_group_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
  $sql = "
  CREATE TABLE $table_name (
  affiliate_org_group_id int(10) NOT NULL AUTO_INCREMENT,
  affiliate_org_id int(10),
  group_name varchar(128),
  PRIMARY KEY  (affiliate_org_group_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}


function ac_report_recreate_affiliate_org_category_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
  $sql = "
  CREATE TABLE $table_name (
  affiliate_org_category_id int(10) NOT NULL AUTO_INCREMENT,
  affiliate_org_id int(10),
  category varchar(128),
  PRIMARY KEY  (affiliate_org_category_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}


function ac_report_recreate_affiliate_org_verification_cache($table_name){
  $sql = "DROP TABLE IF EXISTS $table_name;";
  db_query($sql);
  $sql = "
  CREATE TABLE $table_name (
  affiliate_org_verification_id int(10) NOT NULL AUTO_INCREMENT,
  affiliate_org_id int(10),
  verification varchar(128),
  PRIMARY KEY  (affiliate_org_verification_id)
  ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
      ";
  db_query($sql);  
}

function ac_report_recreate_table_indexes() {
  $sql = "create index proj_aff_project_id on ac_report_project_affiliate_org_cache (project_id)";
  db_query($sql);
  $sql = "create INDEX aff_category_aff_id on ac_report_affiliate_org_category_cache (affiliate_org_id)";
  db_query($sql);
  $sql = "create  INDEX aff_tag_aff_id on ac_report_affiliate_org_tag_cache (affiliate_org_id)";
  db_query($sql);  
  $sql = " CREATE INDEX aff_group_aff_id on ac_report_affiliate_org_group_cache (affiliate_org_id)";
  db_query($sql);    
  $sql = " CREATE INDEX aff_project_aff_id on ac_report_project_affiliate_org_cache (affiliate_org_id)";
  db_query($sql);    
  $sql = " CREATE INDEX aff_producer_prod_id on ac_report_producer_affiliate_org_cache (producer_id)";
  db_query($sql);  
  $sql = " CREATE INDEX item_reservation_prod_id on ac_report_item_reservation_cache (producer_id)";
  db_query($sql);  
  $sql = " CREATE INDEX item_reservation_res_id on ac_report_item_reservation_cache (reservation_id)";
  db_query($sql);  
  $sql = " CREATE INDEX prod_proj_producer_id on ac_report_producer_project_cache (producer_id)";
  db_query($sql);    
  $sql = " CREATE INDEX prod_type_type on ac_report_producer_project_cache (type, producer_id)";
  db_query($sql);
  $sql = " CREATE INDEX prod_class_producer_id on ac_report_producer_class_cache (producer_id)";
  db_query($sql);  
  $sql = " CREATE INDEX class_start_day_class_id on ac_report_class_cache (class_start_day, class_id)";
  db_query($sql);  
  $sql = " CREATE INDEX prod_cert_producer_id on ac_report_producer_certification_cache (producer_id)";
  db_query($sql);    
  $sql = " CREATE INDEX prod_cert_cert_producer_id on ac_report_producer_certification_cache (certification, producer_id)";
  db_query($sql);    
  $sql = " CREATE INDEX prod_group_producer_id on ac_report_producer_group_cache (producer_id)";
  db_query($sql);    
  $sql = " CREATE INDEX prod_group_name_id on ac_report_producer_group_cache (group_name, producer_id  )";
  db_query($sql);  
  $sql = " CREATE INDEX prod_class_class_id on ac_report_producer_class_cache (class_id)";
  db_query($sql);  
  $sql = " CREATE INDEX prod_class_producer_class_id on ac_report_producer_class_cache (producer_id, class_id)";
  db_query($sql);    
  $sql = " CREATE INDEX prod_proj_project_id_producer_id on ac_report_producer_project_cache (producer_id, project_id)";
  db_query($sql);  
  $sql = "create INDEX prod_proj_producer_id_project_id on ac_report_producer_project_cache (project_id, producer_id)";    
  db_query($sql);  
  $sql = "create index proj_exec_producer_id on ac_report_project_cache (exec_producer_id)";
  db_query($sql);  
  $sql = "create index item_res_project_id on ac_report_item_reservation_cache(project_id)";
  db_query($sql);  
  $sql = "create index res_reservation_id_start_time on ac_report_reservation_cache(reservation_id, reserve_start_time )";
  db_query($sql);  
  $sql = "create index res_start_time_reservation_id on ac_report_reservation_cache(reserve_start_time, reservation_id  )";
  db_query($sql);  
  $sql = "create index prod_proj_project_id on ac_report_producer_project_cache(project_id)";
  db_query($sql);  
  $sql = "create index proj_project_id_exec_producer_id on ac_report_project_cache (project_id, exec_producer_id)";
  db_query($sql);  
  $sql = "create index proj_exec_producer_id_project_id on ac_report_project_cache (exec_producer_id, project_id)";
  db_query($sql);  
}
function ac_report_cache_tables_array() {
  $tables = array();
  $sql = "show tables";
  $result = db_query($sql);
  while ($table = db_fetch_array($result)) {
    foreach($table as $name=>$value) {
      $tables[] = $value;
    }
  }
  return $tables;
}

function ac_report_truncate_cache_tables() {
  $tables = ac_report_cache_tables_array();
  foreach($tables as $key=>$table) {
    if ((strpos($table, 'ac_report') === FALSE) ||
        (strpos($table, 'cache') === FALSE)) {
          continue;
    }
    $sql = "TRUNCATE $table;";
    db_query($sql);
  }
}

function ac_report_drop_cache_tables() {
  $tables = ac_report_cache_tables_array();
  foreach($tables as $key=>$table) {
    if ((strpos($table, 'ac_report') === FALSE) ||
        (strpos($table, 'cache') === FALSE)) {
          continue;
    }
    $sql = "DROP TABLE $table;";
    db_query($sql);
  }
}
