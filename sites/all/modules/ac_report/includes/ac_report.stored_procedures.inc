<?
/*
 * Created on Feb 2, 2010
 * Created by Mark Libkuman
 * libkuman@openflows.com
 * www.openflows.com
 * 
 * Created for Manhattan Neighborhood Network
 */

function ac_report_run_stored_procedures($dbname = 'cm_drupal') {

  $stored_procedure_calls = 
    array(
	  "CALL ac_import_reservation(); ",
	  "CALL ac_import_item_reservation(); ",
	  "CALL ac_import_bucket(); ",
	  "CALL ac_import_item(); ",
	  "CALL ac_import_course(); ",
	  "CALL ac_import_class(); ",
	  "CALL ac_import_session(); ",
	  "CALL ac_import_producer_class(); ",
	  "CALL ac_import_producer_session(); ",
	  "CALL ac_import_trainer_class(); ",
	  "CALL ac_import_trainer_session(); ",
	  "CALL ac_import_producer_certification(); ",
	  "CALL ac_import_producer(); ",
	  "CALL ac_import_project(); ",
	  "CALL ac_import_producer_project(); ",
	  "CALL ac_import_airing(); ",
	  "CALL ac_import_episode(); ",
	  "CALL ac_import_affiliate_org(); ",
	  "CALL ac_import_producer_affiliate_org(); ",
	  "CALL ac_import_project_affiliate_org(); ",
	  "CALL  ac_import_producer_group(); ",
	  "CALL  ac_import_affiliate_org_group(); ",
	  "CALL  ac_import_affiliate_org_tag(); ",
	  "CALL  ac_import_affiliate_org_category(); ",
	  "CALL  ac_import_affiliate_org_verification(); ",
	  "CALL ac_import_project_author(); ",
	  );

  $cur = mktime();
  dsm(date('r', $cur));
  foreach ($stored_procedure_calls as $sql) {
    db_query($sql);
  } 

  $end = mktime();

  dsm(date('r', $end));
  dsm($end-$cur);
  //this cleans up the serialized data that is impored for affiliate categories
  //changes it from a category value of a space deliminated set of numbers
  //to multiple rows, one for each category that existed in teh original value
  //i.e. "3 4 6" becomes three separate rows, one value for each of the 3 
  //category id's
  //ac_report_affiliate_category($dbname);

}

function ac_report_recreate_stored_procedures($db) {
  ac_report_recreate_reservation_stored_procedure($db);
  ac_report_recreate_item_reservation_stored_procedure($db);  
  ac_report_recreate_bucket_stored_procedure($db);
  ac_report_recreate_item_stored_procedure($db);
  ac_report_recreate_course_stored_procedure($db);
  ac_report_recreate_class_stored_procedure($db);
  ac_report_recreate_session_stored_procedure($db);
  ac_report_recreate_producer_class_stored_procedure($db);
  ac_report_recreate_producer_session_stored_procedure($db);
  ac_report_recreate_trainer_class_stored_procedure($db);
  ac_report_recreate_trainer_session_stored_procedure($db);
  ac_report_recreate_producer_certification_stored_procedure($db);
  ac_report_recreate_producer_stored_procedure($db);
  ac_report_recreate_project_stored_procedure($db);
  ac_report_recreate_producer_project_stored_procedure($db);
  ac_report_recreate_airing_stored_procedure($db);
  ac_report_recreate_episode_stored_procedure($db);
  ac_report_recreate_affiliate_org_stored_procedure($db);
  ac_report_recreate_producer_affiliate_org_stored_procedure($db);
  ac_report_recreate_project_affiliate_org_stored_procedure($db);
  ac_report_recreate_producer_group_stored_procedure($db);
  ac_report_recreate_affiliate_org_group_stored_procedure($db);
  ac_report_recreate_affiliate_org_tag_stored_procedure($db);
  ac_report_recreate_affiliate_org_category_stored_procedure($db);
  ac_report_recreate_affiliate_org_verification_stored_procedure($db); 
  ac_report_recreate_project_author_stored_procedure($db); 
}
function   ac_report_recreate_project_author_stored_procedure($db){
  $sql = "DROP PROCEDURE IF EXISTS ac_import_project_author";
  db_query($sql);
 
  $sql = "CREATE PROCEDURE ac_import_project_author() ";
  $sql .= "BEGIN ";

  $sql .= "  TRUNCATE ac_report_project_author_cache; ";
  $sql .= "  INSERT INTO ac_report_project_author_cache " .
          "  (project_id, producer_id, producer_name ) " .
          "  SELECT n.nid, n.uid, u.name " .
          "  FROM $db.node n " .
          "  INNER JOIN $db.users u ON u.uid=n.uid " .
    "  WHERE n.type='cm_project'; ";
          
  $sql .= "END ";
  db_query($sql);
}

function ac_report_recreate_reservation_stored_procedure($db){
  $sql = "DROP PROCEDURE IF EXISTS ac_import_reservation";
  db_query($sql);
  
  $sql = "CREATE PROCEDURE ac_import_reservation() ";
  $sql .= "BEGIN ";
  $sql .= "  TRUNCATE ac_report_reservation_cache; ";

  $fields = array(
		  'reservation_id',
		  'producer_id',
		  'reserve_start_time',
		  'reserve_end_time',
		  'inventory_name',
		  'deleted',
		  'note',
		  'reserve_start_int',
		  'reserve_end_int',
		  'reserve_length',
		  );


  $fieldlist_parens = "( ". implode(', ', $fields) ." )";

  // changed $db.reservations_reservation rr ON rr.nid=n.nid - turning on 
  // node revisions for reservations causes a record to be written 
  // to reservations_reservation each time the record is saved and
  // matching nid to nid resulted in too many duplicate records; matching
  // vid allows a result with only the latest version
  // also changed from LEFT join to INNER join
  $sql .= "
   INSERT INTO ac_report_reservation_cache $fieldlist_parens
   SELECT n.nid, n.uid, 
   field_reservations_date_value, field_reservations_date_value2,
   field_reservations_inventory_tid, 
   CASE 
     WHEN reservations_reservation_status = 1 THEN 1
     WHEN reservations_reservation_status = 2 THEN 0
     WHEN reservations_reservation_status = 3 THEN 0
     WHEN reservations_reservation_status = 4 THEN 0
     WHEN reservations_reservation_status = 5 THEN 1
     WHEN reservations_reservation_status = 6 THEN 1
     WHEN reservations_reservation_status = 7 THEN 1
     ELSE 1
   END,
   field_reservation_notes_internal_value, 
   UNIX_TIMESTAMP(field_reservations_date_value),
   UNIX_TIMESTAMP(field_reservations_date_value2),
   UNIX_TIMESTAMP(field_reservations_date_value2) -
   UNIX_TIMESTAMP(field_reservations_date_value)
   FROM $db.node n
   LEFT JOIN $db.field_data_field_reservations_date rd ON rd.entity_id=n.nid
   LEFT JOIN $db.field_data_field_reservations_inventory ri 
     ON ri.entity_id=n.nid
   INNER JOIN $db.reservations_reservation rr ON rr.vid=n.vid
   LEFT JOIN $db.field_data_field_reservation_notes_internal rni 
     ON rni.entity_id=n.nid
   WHERE n.type = 'reservations_reservation'
   GROUP by n.nid
  ;";

  $sql .= "
    UPDATE ac_report_reservation_cache res_cache
    INNER JOIN $db.og_membership m 
      ON (res_cache.reservation_id= m.etid AND m.entity_type = 'node')
    INNER JOIN $db.node proj_node on proj_node.nid=m.gid
    INNER JOIN ac_report_project_cache proj_cache 
      ON proj_cache.project_id=proj_node.nid
    SET res_cache.project_id = proj_node.nid,
        res_cache.project_department = proj_cache.department
    WHERE proj_node.type = 'cm_project'
  ;";

  $sql .= "
    UPDATE ac_report_reservation_cache res_cache
    SET project_id=29999, project_department='Training and Facilitation'
    WHERE project_id is null or project_id=''
  ;";

  $taxonomy_fields = array(
			   'inventory_name',
			   );

  foreach($taxonomy_fields as $tfield) {
    $sql .= "
      UPDATE ac_report_reservation_cache t
      INNER JOIN $db.taxonomy_term_data td on td.tid = t.$tfield
      SET t.$tfield = td.name
    ;";
  }


  $sql .= "END ";
  db_query($sql);
}

function ac_report_recreate_item_reservation_stored_procedure($db){  
  $sql = "DROP PROCEDURE IF EXISTS ac_import_item_reservation";
  db_query($sql);

  $sql = "CREATE PROCEDURE ac_import_item_reservation() ";
  $sql .= "BEGIN ";
  $sql .= "  TRUNCATE ac_report_item_reservation_cache; ";

  $fields = array(
                  'item_reservation_id',		  
		  'bucket_id',
		  'reservation_id',
		  'item_id',
		  'producer_id',
		  'check_out_time',
		  'check_in_time',
		  'check_out_time_int',
		  'check_in_time_int',
		  'check_out_duration',
		 );
  $fieldlist_parens = "( ". implode(', ', $fields) ." )";
  
  // changed $db.reservations_reservation rr ON rr.nid=n.nid - turning on 
  // node revisions for reservations causes a record to be written 
  // to reservations_reservation each time the record is saved and
  // matching nid to nid resulted in too many duplicate records; matching
  // vid allows a result with only the latest version
  // also changed from LEFT join to INNER join  
  $sql .= "
    INSERT INTO ac_report_item_reservation_cache $fieldlist_parens
    SELECT d.did, i.type, r.nid, i.nid, r.uid, 
    field_reservations_date_value, field_reservations_date_value2,
    UNIX_TIMESTAMP(field_reservations_date_value),
    UNIX_TIMESTAMP(field_reservations_date_value2),
    UNIX_TIMESTAMP(field_reservations_date_value2) -
    UNIX_TIMESTAMP(field_reservations_date_value)
    FROM $db.reservations_reservation_detail d 
    INNER JOIN $db.node r ON d.vid=r.vid 
    LEFT JOIN $db.node i ON i.nid=d.reservations_item_nid 
    LEFT JOIN $db.field_data_field_reservations_date rd ON rd.revision_id=r.vid
    ;";

    $sql .= "
      UPDATE ac_report_item_reservation_cache ir
      INNER JOIN $db.reservations_reservation_detail d 
        on d.did=ir.item_reservation_id
      INNER JOIN $db.node p on p.nid=d.reservations_placeholder_nid
      SET bucket_id = p.type, item_id=reservations_item_nid
      WHERE bucket_id is null
      ;";


    $sql .= "
      UPDATE ac_report_item_reservation_cache ir
      INNER JOIN $db.node r ON ir.reservation_id=r.nid 
      INNER JOIN $db.og_membership m 
        ON (ir.reservation_id = m.etid AND m.entity_type = 'node')
      INNER JOIN $db.node p on p.nid=m.gid
      SET ir.project_id = p.nid
      WHERE p.type='cm_project'
     ;";

    $sql .= "
      UPDATE ac_report_item_reservation_cache
      SET project_id=29999
      WHERE project_id is null
    ;";

  $sql .= "END ";
  db_query($sql);
}
function ac_report_recreate_bucket_stored_procedure($db){
  $sql = "DROP PROCEDURE IF EXISTS ac_import_bucket";
  db_query($sql);
  $sql = "CREATE PROCEDURE ac_import_bucket() ";
  $sql .= "BEGIN ";
  $sql .= "  TRUNCATE ac_report_bucket_cache; ";

  $fields = array(
		  'bucket_id',
		  'title',
		  'bucket_type',
		  'price',
		  'bucket_category',
		  'inventory_name',
		  );
 
  $fieldlist_parens = "( ". implode(', ', $fields) ." )";
  
  $sql .= "
    INSERT INTO ac_report_bucket_cache $fieldlist_parens
    SELECT nt.type, nt.name, 
    CASE 
      WHEN rrn.nid is NOT NULL THEN 'facility'     
      WHEN rrn.nid is NOT NULL THEN 'equipment'
      ELSE 'equipment'
    END,     
    rnt.reservations_rate_per_hour, ttd.name, inv.tids
    FROM $db.node i 
    INNER JOIN $db.node_type nt ON nt.type=i.type
    INNER JOIN $db.reservations_node_type rnt ON nt.type=rnt.type
    INNER JOIN $db.reservations_inventory_node_type inv ON i.type=inv.type
    INNER JOIN $db.reservations_reservation_item_node rin ON rin.nid=i.nid 
    LEFT JOIN $db.reservations_resource_node rrn ON rrn.nid=i.nid
    LEFT JOIN $db.reservations_bucket_node rbn ON rbn.nid=i.nid
    LEFT JOIN $db.taxonomy_term_data ttd on ttd.tid=rnt.reservations_grouping
    WHERE rin.reservations_sub_type !=2
    AND (rrn.nid is NULL OR rrn.reservations_sub_type !=2)
    AND (rbn.nid is NULL OR rbn.reservations_sub_type !=2)
    group by nt.type, nt.name
  ;";

  $taxonomy_fields = array(
			   'inventory_name',
			   );

  foreach($taxonomy_fields as $tfield) {
    $sql .= "
      UPDATE ac_report_bucket_cache t
      INNER JOIN $db.taxonomy_term_data td on td.tid = t.$tfield
      SET t.$tfield = td.name
    ;";
  }

  foreach($taxonomy_fields as $tfield) {
    $sql .= "
      UPDATE ac_report_bucket_cache t
      SET t.$tfield = 'Other'
      WHERE t.$tfield REGEXP '^-?[0-9]+$' OR
      t.$tfield is NULL OR
      t.$tfield = ''
    ;";
  }

  $sql .= "
    UPDATE ac_report_reservation_cache r
    INNER JOIN ac_report_item_reservation_cache i using(reservation_id)
    INNER JOIN ac_report_bucket_cache b USING(bucket_id)
    SET r.type = b.bucket_type
  ;";

  $sql .= "END ";
  db_query($sql);
}
function ac_report_recreate_item_stored_procedure($db){
  $sql = "DROP PROCEDURE IF EXISTS ac_import_item";
  db_query($sql);
  
  $sql = "CREATE PROCEDURE ac_import_item() ";
  $sql .= "BEGIN ";

  $sql .= "  TRUNCATE ac_report_item_cache; ";    


  $fields = array(
		  'item_id',
		  'title',
		  'facility_name',
		  'item_type',
		  'bucket_id',
		  'facility_code',
		  'serial_number',
		  'inventory_number',
		  'location',
		  'location_item_id',
		  'item_status',
		  'inventory_name',
		  'department_name',
		  );
 
  $fieldlist_parens = "( ". implode(', ', $fields) ." )";
  
  $sql .= "
    INSERT INTO ac_report_item_cache $fieldlist_parens
    SELECT i.nid, i.title, 
    CASE 
      WHEN rrn.nid is NOT NULL THEN i.title
      ELSE ''
    END,     
    CASE 
      WHEN rrn.nid is NOT NULL THEN 'facility'     
      WHEN rbn.nid is NOT NULL THEN 'equipment'
      ELSE 'equipment'
    END,     
    nt.type, field_facility_code_value, field_serial_number_value, 
    field_inventory_number_value, field_associated_facility_nid,
    field_associated_facility_nid, field_equipment_item_status_tid,
    field_reservations_inventory_tid, field_department_tid   

    FROM $db.node i 
    LEFT JOIN $db.field_data_field_serial_number sn on sn.revision_id=i.vid 
    INNER JOIN $db.node_type nt on nt.type=i.type 
    INNER JOIN $db.reservations_node_type rnt on nt.type=rnt.type 
    INNER JOIN $db.reservations_inventory_node_type inv ON i.type=inv.type 
    INNER JOIN $db.reservations_reservation_item_node rin ON rin.nid=i.nid 
    LEFT JOIN $db.reservations_resource_node rrn on rrn.nid=i.nid 
    LEFT JOIN $db.reservations_bucket_node rbn on rbn.nid=i.nid
    INNER JOIN $db.taxonomy_term_data ttd on ttd.tid=rnt.reservations_grouping 
    LEFT JOIN $db.field_data_field_facility_code fc on fc.revision_id=i.vid
    LEFT JOIN $db.field_data_field_inventory_number in_num 
      on in_num.revision_id=i.vid
    LEFT JOIN $db.field_data_field_associated_facility af 
      on af.revision_id=i.vid
    LEFT JOIN $db.field_data_field_equipment_item_status istat 
      on istat.revision_id=i.vid
    LEFT JOIN $db.field_data_field_department dept on dept.revision_id=i.vid
    LEFT JOIN $db.field_data_field_reservations_inventory inv_name
      on inv_name.revision_id=i.vid
    WHERE rin.reservations_sub_type !=2
    AND (rrn.nid is NULL OR rrn.reservations_sub_type !=2)
    AND (rbn.nid is NULL OR rbn.reservations_sub_type !=2)
    AND i.type!='equipment_non_reservable_'
    AND i.type!='facility_non_reservable_'
    GROUP BY i.nid, i.title
  ;";
  

  $sql .= "
    INSERT INTO ac_report_item_cache $fieldlist_parens
    SELECT i.nid, i.title, i.title, 'facility', 'facility_non_reservable_',
    field_facility_code_value, '', '', field_associated_facility_nid,
    field_associated_facility_nid, field_equipment_item_status_tid,
    field_reservations_inventory_tid, field_department_tid   

    FROM $db.node i 
    LEFT JOIN $db.field_data_field_facility_code fc on fc.revision_id=i.vid
    LEFT JOIN $db.field_data_field_associated_facility af 
      on af.revision_id=i.vid
    LEFT JOIN $db.field_data_field_equipment_item_status istat 
      on istat.revision_id=i.vid
    LEFT JOIN $db.field_data_field_department dept on dept.revision_id=i.vid
    LEFT JOIN $db.field_data_field_reservations_inventory inv_name
      on inv_name.revision_id=i.vid
    WHERE i.type = 'facility_non_reservable_'
    GROUP BY i.nid, i.title
  ;";

  $sql .= "
    INSERT INTO ac_report_item_cache $fieldlist_parens
    SELECT i.nid, i.title, '', 'equipment', 'equipment_non_reservable_',
    '', field_serial_number_value, field_inventory_number_value, 
    field_associated_facility_nid, field_associated_facility_nid, 
    field_equipment_item_status_tid, field_reservations_inventory_tid, 
    field_department_tid   

    FROM $db.node i 
    INNER JOIN $db.field_data_field_serial_number sn on sn.revision_id=i.vid 
    LEFT JOIN $db.field_data_field_inventory_number in_num 
      on in_num.revision_id=i.vid
    LEFT JOIN $db.field_data_field_associated_facility af 
      on af.revision_id=i.vid
    LEFT JOIN $db.field_data_field_equipment_item_status istat 
      on istat.revision_id=i.vid
    LEFT JOIN $db.field_data_field_department dept on dept.revision_id=i.vid
    LEFT JOIN $db.field_data_field_reservations_inventory inv_name
      on inv_name.revision_id=i.vid
    WHERE i.type = 'equipment_non_reservable_'
    GROUP BY i.nid, i.title
  ;";

  $taxonomy_fields = array(
			   'item_status',
			   'inventory_name',
			   'department_name',
			   );

  foreach($taxonomy_fields as $tfield) {
    $sql .= "
      UPDATE ac_report_item_cache t
      INNER JOIN $db.taxonomy_term_data td on td.tid = t.$tfield
      SET t.$tfield = td.name
    ;";
  }

  foreach($taxonomy_fields as $tfield) {
    $sql .= "
      UPDATE ac_report_item_cache t
      SET t.$tfield = 'Other'
      WHERE t.$tfield REGEXP '^-?[0-9]+$' OR
      t.$tfield is NULL OR
      t.$tfield = ''
    ;";
  }

  $sql .= "
    UPDATE ac_report_item_cache t
    INNER JOIN $db.node n  on n.nid=t.location_item_id
    SET t.location = n.title
  ;";


  $sql .= "END ";
  db_query($sql);
}
function ac_report_recreate_course_stored_procedure($db){
  $sql = "DROP PROCEDURE IF EXISTS ac_import_course";
  db_query($sql);
  
  $sql = "CREATE PROCEDURE ac_import_course() ";
  $sql .= "BEGIN ";
  $sql .= "  TRUNCATE ac_report_course_cache; ";
  $sql .= "END ";
  db_query($sql);
}
function ac_report_recreate_class_stored_procedure($db){
  $civi_db = ac_report_civi_db($db);

  $sql = "DROP PROCEDURE IF EXISTS ac_import_class";
  db_query($sql);
  
  $sql = "CREATE PROCEDURE ac_import_class() ";
  $sql .= "BEGIN ";
  $sql .= "  TRUNCATE ac_report_class_cache; ";

  $fields = array(
		  'event_id',
		  'title',
		  'created',
		  'course_title',
		  'certification',
		  'course_type',
		  'capacity',
		  'number_attended',
		  'language',
		  'building',
		  'department',
		  'class_start_day',
		  'affiliate_org_id',
		  'legacy_class_id'
		  );

  $fieldlist_parens = "( ". implode(', ', $fields) ." )";
  
  $sql .= "
    INSERT INTO ac_report_class_cache $fieldlist_parens
    SELECT e.id, e.title, e.created_date, e.template_title, cr.cert_rule_group,
    'Normal', e.max_participants, field_class_attendance_value,
    field_pbcore_languages_tid, field_building_tid, field_department_tid, 
    e.start_date, af_org.field_affiliate_org_contact_id, mde.nid
    FROM $db.node mde
    INNER JOIN $db.field_data_field_civievent_id eid_field 
      ON eid_field.revision_id=mde.vid
    LEFT JOIN $db.field_data_field_building b ON b.revision_id=mde.vid
    LEFT JOIN $db.field_data_field_pbcore_languages l ON l.revision_id=mde.vid
    LEFT JOIN $db.field_data_field_department d on d.revision_id=mde.vid
    LEFT JOIN $db.field_data_field_class_attendance a ON a.revision_id=mde.vid
    LEFT JOIN $db.field_data_field_affiliate_org af_org 
      ON af_org.revision_id=mde.vid
    INNER JOIN $civi_db.civicrm_event e 
      ON eid_field.field_civievent_id_value = e.id
    LEFT JOIN $db.certification_rule cr  
      ON cr.cert_rule_event_type = e.event_type_id

    ;";

  $taxonomy_fields = array(		  
		  'language', 
		  'department', 
		  'building',
		  );

  foreach($taxonomy_fields as $tfield) {
    $sql .= "
      UPDATE ac_report_class_cache t
      INNER JOIN $db.taxonomy_term_data td on td.tid = t.$tfield
      SET t.$tfield = td.name
    ;";
  }

  //UPDATE CERTIFICATION TO BE THE ROLE NAME
  $sql .= "
    UPDATE ac_report_class_cache c
    LEFT JOIN $db.civicrm_group_roles_rules cgrr 
      ON c.certification = cgrr.group_id
    SET c.certification=NULL
    WHERE cgrr.id is NULL
  ;";

  $sql .= "
    UPDATE ac_report_class_cache c
    INNER JOIN $db.civicrm_group_roles_rules cgrr 
      ON c.certification = cgrr.group_id
    INNER JOIN $db.role r on r.rid = cgrr.role_id
    SET c.certification=r.name
  ;";

  //0. number_producer_students
  //3. student_list

  $attendee_role = 1;
  $sql .= "
    UPDATE ac_report_class_cache c
    INNER JOIN(
      SELECT p.event_id, GROUP_CONCAT(c.display_name SEPARATOR ' --- ') as names, 
      count(p.event_id) as student_count
      FROM $civi_db.civicrm_contact c
      INNER JOIN $civi_db.civicrm_participant p ON c.id=p.contact_id
      INNER JOIN $civi_db.civicrm_participant_status_type cps
      ON cps.id=p.status_id
      WHERE (
        lower(cps.name)='registered' OR
        lower(cps.name)='attended' OR
        lower(cps.name)='passed' 
      )
      GROUP BY p.event_id) cp ON c.event_id=cp.event_id
    SET number_producer_students= cp.student_count,
      student_list=cp.names
  ;";
  
  //number_of_sessions
  //session_hours                                                            
  $sql .= "  
    UPDATE ac_report_class_cache c
    INNER JOIN(
      SELECT e.field_civievent_id_value as event_id,count(1) as num_sess_count,
      SUM(UNIX_TIMESTAMP(field_session_date_value2) -
          UNIX_TIMESTAMP(field_session_date_value)) as sess_length
      FROM $db.node mde
      INNER JOIN $db.field_data_field_civievent_id e
        ON e.entity_id=mde.nid
      INNER JOIN $db.field_data_field_civicrm_multiday_session cms
        ON cms.entity_id=mde.nid
      INNER JOIN $db.field_data_field_session_date sd 
        ON sd.entity_id=cms.field_civicrm_multiday_session_value
      GROUP BY e.field_civievent_id_value
    ) sessions ON sessions.event_id=c.event_id
    SET c.number_of_sessions = sessions.num_sess_count,
        c.session_hours = (sessions.sess_length/(60*60))
  ;";

  //primary_trainer_name
  $sql .= "
    UPDATE ac_report_class_cache c
    INNER JOIN $db.field_data_field_civievent_id e
      ON e.field_civievent_id_value = c.event_id
    INNER JOIN $db.node mde ON mde.nid=e.entity_id
    INNER JOIN $db.field_data_field_civicrm_multiday_session cms
      ON cms.entity_id=mde.nid
    INNER JOIN $db.field_data_field_trainer st 
      ON st.entity_id=cms.field_civicrm_multiday_session_value
    INNER JOIN $civi_db.civicrm_uf_match m ON m.uf_id = st.field_trainer_uid
    INNER JOIN $civi_db.civicrm_contact cc ON cc.id=m.contact_id
    SET c.primary_trainer_name=cc.display_name
  ;";
    
  //4. affiliate_org_name
  $sql .= "
    UPDATE ac_report_class_cache c
    INNER JOIN $civi_db.civicrm_contact cc on c.affiliate_org_id=cc.id
    SET c.affiliate_org_name=cc.display_name
  ;";


  $sql .= "END ";
  db_query($sql);
}



function ac_report_recreate_producer_class_stored_procedure($db){
  $civi_db = ac_report_civi_db($db);
  $sql = "DROP PROCEDURE IF EXISTS ac_import_producer_class";
  db_query($sql);
  
  $sql = "CREATE PROCEDURE ac_import_producer_class() ";
  $sql .= "BEGIN ";
  $sql .= "  TRUNCATE ac_report_producer_class_cache; ";
  $fields = array('participant_id',
		  'class_id',
		  'producer_id',
		  'contact_id',
		  'affiliate_org_id',
		  'status',
		  );

  $fieldlist_parens = "( ". implode(', ', $fields) ." )";
  
  // left join for uf_match to take care of duplicates in civicrm
  $sql .= "
    INSERT INTO ac_report_producer_class_cache $fieldlist_parens
    SELECT cp.id, c.class_id, m.uf_id, cp.contact_id, c.affiliate_org_id, 
    CASE
      WHEN cps.name='Attended' THEN 'passed'
      WHEN cps.name='Cancelled' THEN 'cancelled'
      WHEN cps.name='No-show' THEN 'cancelled'      
      WHEN cps.name='passed' THEN 'passed'
      WHEN cps.name='Pending from pay later' THEN 'unconfirmed'
      WHEN cps.name='Registered' THEN 'passed'
    END
    FROM $civi_db.civicrm_participant cp
    INNER JOIN ac_report_class_cache c ON c.event_id=cp.event_id
    LEFT JOIN $civi_db.civicrm_uf_match m on m.contact_id=cp.contact_id
    INNER JOIN $civi_db.civicrm_participant_status_type cps
      ON cps.id=cp.status_id
    ;";
 
 $sql .= "END ";
  db_query($sql);
}
function ac_report_recreate_trainer_class_stored_procedure($db){
  
  $sql = "DROP PROCEDURE IF EXISTS ac_import_trainer_class";
  db_query($sql);
  
  $sql = "CREATE PROCEDURE ac_import_trainer_class() ";
  $sql .= "BEGIN ";
  $sql .= "  TRUNCATE ac_report_trainer_class_cache; ";

  $fields = array('class_id',
		  'producer_id',
		  'type',
		  );

  $fieldlist_parens = "( ". implode(', ', $fields) ." )";
  
  $sql .= "
    INSERT INTO ac_report_trainer_class_cache $fieldlist_parens
    SELECT c.class_id, st.field_trainer_uid, 'Primary'
    FROM ac_report_class_cache c
    INNER JOIN $db.field_data_field_civievent_id e
      ON e.field_civievent_id_value = c.event_id
    INNER JOIN $db.node mde ON mde.nid=e.entity_id
    INNER JOIN $db.field_data_field_civicrm_multiday_session cms
      ON cms.entity_id=mde.nid
    INNER JOIN $db.field_data_field_trainer st 
      ON st.entity_id=cms.field_civicrm_multiday_session_value
  ;";

  $sql .= "END ";
  db_query($sql);
  
}
function ac_report_recreate_session_stored_procedure($db){
  $sql = "DROP PROCEDURE IF EXISTS ac_import_session";
  db_query($sql);
  
  $sql = "CREATE PROCEDURE ac_import_session() ";
  $sql .= "BEGIN ";
  $sql .= "  TRUNCATE ac_report_session_cache; ";
  $sql .= "END ";
  db_query($sql);
}
function ac_report_recreate_producer_session_stored_procedure($db){
 $sql = "DROP PROCEDURE IF EXISTS ac_import_producer_session";
  db_query($sql);
  
  $sql = "CREATE PROCEDURE ac_import_producer_session() ";
  $sql .= "BEGIN ";
  $sql .= "  TRUNCATE ac_report_producer_session_cache; ";
  $sql .= "END ";
  db_query($sql);
}                        
function ac_report_recreate_trainer_session_stored_procedure($db){
  
  $sql = "DROP PROCEDURE IF EXISTS ac_import_trainer_session";
  db_query($sql);
  
  $sql = "CREATE PROCEDURE ac_import_trainer_session() ";
  $sql .= "BEGIN ";
  $sql .= "  TRUNCATE ac_report_trainer_session_cache; ";
  $sql .= "END ";
  db_query($sql);
  
}

function ac_report_recreate_producer_stored_procedure($db){
  $sql = "DROP PROCEDURE IF EXISTS ac_import_producer";
  db_query($sql);

  $civi_db = ac_report_civi_db($db);
  
  $sql = "CREATE PROCEDURE ac_import_producer() ";
  $sql .= "BEGIN ";
  $sql .= "  TRUNCATE ac_report_producer_cache; ";
  $sql .= 
    "  INSERT INTO ac_report_producer_cache" .
    "  (producer_id, username, email, created ) " .
    "    SELECT uid, name, mail, created " .
    "    FROM $db.users WHERE uid != 0;";
  

  $sql .= "UPDATE ac_report_producer_cache p " .
    "INNER JOIN $civi_db.civicrm_uf_match m " .
    "  ON p.producer_id=m.uf_id  " .
    "INNER JOIN $civi_db.civicrm_contact c " .
    "  ON c.id=m.contact_id " .
    "SET p.display_name = c.display_name; ";
  
  $sql .= "UPDATE ac_report_producer_cache p " .
           "INNER JOIN $civi_db.civicrm_uf_match m on m.uf_id=p.producer_id " .
           "INNER JOIN $civi_db.civicrm_phone ph on ph.contact_id=m.contact_id " .
           "INNER JOIN $civi_db.civicrm_location_type lt 
              on lt.id=ph.location_type_id " .
           "SET p.phone_primary = ph.phone " .
           "WHERE lt.name='Home'; ";

  $sql .= "UPDATE ac_report_producer_cache p " .
           "INNER JOIN $civi_db.civicrm_uf_match m on m.uf_id=p.producer_id " .
           "INNER JOIN $civi_db.civicrm_phone ph on ph.contact_id=m.contact_id " .
           "INNER JOIN $civi_db.civicrm_location_type lt 
              on lt.id=ph.location_type_id " .
           "SET p.phone_other = ph.phone " .
           "WHERE lt.name='Other'; ";

  $sql .= 
    "UPDATE ac_report_producer_cache p " .
    "INNER JOIN $civi_db.civicrm_uf_match m on m.uf_id=p.producer_id " .
    "INNER JOIN $civi_db.civicrm_address a on a.contact_id=m.contact_id " .
    "INNER JOIN $civi_db.civicrm_location_type lt on lt.id=a.location_type_id " .
    "INNER JOIN $civi_db.civicrm_state_province sp on sp.id=a.state_province_id " .
    "LEFT  JOIN $civi_db.nyc_zipcodes z on a.postal_code=z.zipcode " .
    "SET p.street_address = a.street_address, " .
    "p.city = a.city, p.state=sp.name, p.zip=a.postal_code, " .
    "p.borough=z.borough " .
    "WHERE lt.name='Home';";
  
  
  $sql .= " UPDATE ac_report_producer_cache p".
    " INNER JOIN ".
    " ( SELECT producer_id, COUNT(*) AS class_count ".
    " FROM ac_report_producer_class_cache ".
    " GROUP BY producer_id ) pc ".
    " ON pc.producer_id = p.producer_id ".
    " SET p.number_of_classes = pc.class_count ".
    " ; ";
  
   $sql .= " UPDATE ac_report_producer_cache p
            INNER JOIN 
              (SELECT e.exec_producer_id, COUNT(*) as episode_count
               FROM ac_report_episode_cache e
               GROUP BY e.exec_producer_id) eep
             ON p.producer_id=eep.exec_producer_id 
             SET p.number_of_episodes = eep.episode_count;";

   $sql .= "UPDATE ac_report_producer_cache p " .
     "INNER JOIN " .
     "    (SELECT producer_id, count(1) as reservation_count " .
     "     FROM ac_report_item_reservation_cache " .
     "     GROUP BY producer_id) as reservations " .
     "  ON reservations.producer_id=p.producer_id " .
     "SET p.number_of_reservations = reservations.reservation_count; ";

   $sql .= "UPDATE ac_report_producer_cache p ".
     "SET p.number_of_activities = " .
     "  (IF(p.number_of_classes,     p.number_of_classes,      0) + " .
     "   IF(p.number_of_projects,    p.number_of_projects,     0) + " .
     "   IF(p.number_of_episodes,    p.number_of_episodes,     0) +  " .
     "   IF(p.number_of_reservations,p.number_of_reservations, 0)); ";

   $sql .= "  UPDATE ac_report_class_cache class " .
     "  INNER JOIN ac_report_trainer_class_cache tc " .
     "    on tc.class_id=class.class_id " .
     "  INNER JOIN ac_report_producer_cache producer " .
     "    ON producer.producer_id=tc.producer_id ".
     "  SET class.primary_trainer_name = producer.display_name ;";

   $sql .= "
     UPDATE ac_report_producer_cache p
     INNER JOIN $civi_db.civicrm_uf_match m on m.uf_id=p.producer_id 
     LEFT JOIN $civi_db.civicrm_value_verifications_2 v on v.entity_id=m.contact_id
     SET verified = 
       CASE 
         WHEN v.identity_verified_7 THEN 'YES'
         ELSE 'NO'
       END,
     verification_date=v.verification_date_8;";


   $sql .= "END ";
   db_query($sql);
}

function ac_report_recreate_project_stored_procedure($db){
  $object  = 'project';

  $procedure_name = "ac_import_".$object;
  $table_name = "ac_report_".$object."_cache";

  $sql = "DROP PROCEDURE IF EXISTS ".$procedure_name;
  db_query($sql);
  $sql = "CREATE PROCEDURE ".$procedure_name."()".
    " BEGIN ".
    "  TRUNCATE $table_name; ";

  $fields = array(
		  'project_id',
		  'node_id', 
		  'title',
		  'created',
		  'changed', 
		  'exec_producer_id',
		  'narrative',
		  'public_contact_info',
		  'public_url',
		  'public_email_value',
		  'project_status', 
		  '`interval`', 
		  'language', 
		  'department', 
		  'format', 
		  'topic', 
		  'schedule_type',
		  'device',
		  'runtime',
		  'deactivation_date',
		  );
  $fieldlist_parens = "( ". implode(', ', $fields) ." )";
  $sql .= "
   INSERT INTO $table_name $fieldlist_parens

   SELECT n.nid, n.nid, n.title, FROM_UNIXTIME(n.created), 
     FROM_UNIXTIME(n.changed), n.uid,
     d.field_description_value, pc.field_public_contact_value,
     pu.field_project_public_url_value, pe.field_project_public_email_value,
     
   CASE 
     WHEN gg.group_group_value = 1 THEN 'Active'
     WHEN rna.field_reason_not_active_tid IS NULL AND gg.group_group_value = 0
       THEN 'Inactive'
     ELSE rna.field_reason_not_active_tid
   END,

   i.field_interval_tid, l.field_pbcore_languages_tid, dp.field_department_tid,
   f.field_format_tid, pbc.field_pbcore_genres_tid, 
   pt.taxonomy_cm_project_types_tid, dv.field_device_tid,
   rt.field_runtime_tid, dd.field_deactivation_date_value

   FROM $db.node n 
   LEFT JOIN $db.field_data_field_description d ON d.revision_id=n.vid
   LEFT JOIN $db.field_data_field_public_contact pc ON pc.revision_id=n.vid
   LEFT JOIN $db.field_data_field_project_public_url pu ON pu.revision_id=n.vid
   LEFT JOIN $db.field_data_field_project_public_email pe 
     ON pe.revision_id=n.vid
   LEFT JOIN $db.field_data_group_group gg 
     ON n.nid = gg.entity_id AND (gg.entity_type = 'node' AND gg.deleted = '0')
   LEFT JOIN $db.field_data_field_reason_not_active rna 
     ON rna.revision_id=n.vid 
   LEFT JOIN $db.field_data_field_interval i ON i.revision_id=n.vid
   LEFT JOIN $db.field_data_field_pbcore_languages l ON l.revision_id=n.vid
   LEFT JOIN $db.field_data_field_department dp ON dp.revision_id=n.vid
   LEFT JOIN $db.field_data_field_format f ON f.revision_id=n.vid
   LEFT JOIN $db.field_data_field_pbcore_genres pbc ON pbc.revision_id=n.vid
   LEFT JOIN $db.field_data_taxonomy_cm_project_types  pt 
     ON pt.revision_id=n.vid
   LEFT JOIN $db.field_data_field_device dv ON dv.revision_id=n.vid
   LEFT JOIN $db.field_data_field_runtime rt ON rt.revision_id=n.vid
   LEFT JOIN $db.field_data_field_deactivation_date dd 
     ON dd.revision_id=n.vid
   WHERE n.type='cm_project'
   
  ;";

  $taxonomy_fields = array(		  
		  'project_status', 
		  '`interval`', 
		  'language', 
		  'department', 
		  'format', 
		  'topic', 
		  'schedule_type',
		  'device',
		  'runtime',
		  );

  foreach($taxonomy_fields as $tfield) {
    $sql .= "
      UPDATE $table_name t
      INNER JOIN $db.taxonomy_term_data td on td.tid = t.$tfield
      SET t.$tfield = td.name
    ;";
  }

  foreach($taxonomy_fields as $tfield) {
    $sql .= "
      UPDATE $table_name t
      SET t.$tfield = 'Other'
      WHERE t.$tfield REGEXP '^-?[0-9]+$' OR
      t.$tfield is NULL OR
      t.$tfield like '_N'
    ;";
  }


  $sql .= "END ";
  db_query($sql);
}

function ac_report_recreate_episode_stored_procedure($db){
  $object  = 'episode';
  $procedure_name = "ac_import_".$object;
  $table_name = "ac_report_".$object."_cache";

  $sql = "DROP PROCEDURE IF EXISTS ".$procedure_name;
  db_query($sql);
  $sql = "CREATE PROCEDURE ".$procedure_name."()".
    " BEGIN ".
    "  TRUNCATE $table_name; ";

  $fields = array(
		  'episode_id',
		  'episode_number', 
		  'project_id',
		  'exec_producer_id',
		  'associate_producer_name',
		  'special_producer_email',
		  'special_producer_website',
		  'special_producer_address',
		  'special_producer_phone',  		  
		  'title',		                     
                  'narrative',               
                  'notes',                   
		  'created',
		  'changed',
		  'duration',  
		  'time_code_in',
		  'time_code_out',
		  'timing_duration',
		  'transcoded_time_code_in',
		  'transcoded_time_code_out',
		  'runtime_type',
		  'language',
		  'audience',
		  'content_type',
		  'format',
		  'topic',
		  'schedule_type',
		  'live_device',
		  'reject_reason',
		  'delivered_via',
		  /*              
		  'first_airing_time',
		  'last_airing_time',
		  'number_of_airings',
*/

		  );
  $fieldlist_parens = "( ". implode(', ', $fields) ." )";
  $sql .= "
   INSERT INTO $table_name $fieldlist_parens

   SELECT n.nid, en.field_episode_number_value, m.gid, 
     proj_node.uid, field_producer_name_value, field_producer_email_value, 
     field_producer_website_value, field_producer_address_value,      
     field_producer_phone_value, n.title, field_narrative_value, field_notes_value,
     FROM_UNIXTIME(n.created), FROM_UNIXTIME(n.changed),
     CASE
       WHEN (field_trans_timecode_in_value IS NOT NULL AND 
             field_trans_timecode_out_value is NOT NULL AND
             (field_trans_timecode_out_value - field_trans_timecode_in_value) > 0 AND
             (field_trans_timecode_out_value - field_trans_timecode_in_value) < 10000)
       THEN field_trans_timecode_out_value - field_trans_timecode_in_value
       WHEN (field_timecode_in_value IS NOT NULL AND 
             field_timecode_out_value is NOT NULL AND
             (field_timecode_out_value - field_timecode_in_value) > 0 AND
             (field_timecode_out_value - field_timecode_in_value) < 10000)
       THEN field_timecode_out_value - field_timecode_in_value
       WHEN field_runtime_tid=850 THEN 28*60 
       WHEN field_runtime_tid=851 THEN 58*60 
       WHEN field_runtime_tid=852 THEN 88*60 
       WHEN field_runtime_tid=853 THEN 118*60 
       ELSE 1
     END duration,
     field_timecode_in_value, field_timecode_out_value,
     CASE
       WHEN (field_trans_timecode_in_value IS NOT NULL AND 
             field_trans_timecode_out_value is NOT NULL AND
             (field_trans_timecode_out_value - field_trans_timecode_in_value) > 0)
       THEN field_trans_timecode_out_value - field_trans_timecode_in_value
       WHEN (field_timecode_in_value IS NOT NULL AND 
             field_timecode_out_value is NOT NULL AND
             (field_timecode_out_value - field_timecode_in_value) > 0)
       THEN field_timecode_out_value - field_timecode_in_value
       ELSE 1
     END timing_duration,
     field_trans_timecode_in_value, field_trans_timecode_out_value,
     CASE
       WHEN field_runtime_tid=850 THEN '28 mins' 
       WHEN field_runtime_tid=851 THEN '58 mins'
       WHEN field_runtime_tid=852 THEN '88 mins'
       WHEN field_runtime_tid=853 THEN '118 mins'
       ELSE 'Other'
     END runtime_type,
     field_pbcore_languages_tid, '', field_pbcore_genres_tid, field_format_tid,
     '', taxonomy_cm_project_types_tid, field_device_tid, field_reject_reason_tid,
     field_delivered_via_tid

		

   FROM $db.node n 
   LEFT JOIN $db.field_data_field_episode_number en ON en.revision_id=n.vid
   LEFT JOIN $db.og_membership m ON (n.nid = m.etid AND m.entity_type = 'node')
   LEFT JOIN $db.node proj_node on proj_node.nid=m.gid
   LEFT JOIN $db.field_data_field_producer_name fpn ON n.vid=fpn.revision_id
   LEFT JOIN $db.field_data_field_producer_email fpe ON n.vid=fpe.revision_id
   LEFT JOIN $db.field_data_field_producer_website fpw ON n.vid=fpw.revision_id
   LEFT JOIN $db.field_data_field_producer_address fpa ON n.vid=fpa.revision_id
   LEFT JOIN $db.field_data_field_producer_phone fpp ON n.vid=fpp.revision_id
   LEFT JOIN $db.field_data_field_narrative fn on n.vid=fn.revision_id
   LEFT JOIN $db.field_data_field_notes fnt on n.vid=fnt.revision_id
   LEFT JOIN $db.field_data_field_trans_timecode_in tti on n.vid=tti.revision_id
   LEFT JOIN $db.field_data_field_trans_timecode_out tto on n.vid=tto.revision_id
   LEFT JOIN $db.field_data_field_timecode_in ti on n.vid=ti.revision_id
   LEFT JOIN $db.field_data_field_timecode_out tout on n.vid=tout.revision_id
   LEFT JOIN $db.field_data_field_runtime rt on n.vid=rt.revision_id
   LEFT JOIN $db.field_data_field_pbcore_languages pl on n.vid=pl.revision_id
   LEFT JOIN $db.field_data_field_pbcore_genres pg on n.vid=pg.revision_id
   LEFT JOIN $db.field_data_field_format ff on n.vid=ff.revision_id
   LEFT JOIN $db.field_data_taxonomy_cm_project_types pt on n.vid=pt.revision_id
   LEFT JOIN $db.field_data_field_device fd on n.vid=fd.revision_id
   LEFT JOIN $db.field_data_field_reject_reason rr on n.vid=rr.revision_id
   LEFT JOIN $db.field_data_field_delivered_via dv on n.vid=dv.revision_id
   

   WHERE n.type='cm_show'
   group by n.nid
   ;";

  $taxonomy_fields = array(		  
			   'language',              
			   'content_type',          
			   'format',                
			   'schedule_type',         
			   'live_device',           
			   'reject_reason',         
			   'delivered_via'         
					  );

  foreach($taxonomy_fields as $tfield) {
    $sql .= "
      UPDATE $table_name t
      INNER JOIN $db.taxonomy_term_data td on td.tid = t.$tfield
      SET t.$tfield = td.name
    ;";
  }

  foreach($taxonomy_fields as $tfield) {
    $sql .= "
      UPDATE $table_name t
      SET t.$tfield = 'Other'
      WHERE t.$tfield REGEXP '^-?[0-9]+$' OR
      t.$tfield is NULL OR
      t.$tfield like '_N'
    ;";
  }

  $sql .= "
    UPDATE $table_name as episode,
    (
     SELECT episode_id, 
     MIN(start_time) as min_start, MAX(end_time) as max_start,
     COUNT(airing_id) as airing_count
     FROM ac_report_airing_cache
     group by episode_id
     ) as airing_info
     SET episode.first_airing_time = airing_info.min_start, 
     episode.last_airing_time = airing_info.max_start, 
     episode.number_of_airings = airing_info.airing_count 
     WHERE episode.episode_id = airing_info.episode_id
   ;";
 

  $sql .= "
    UPDATE ac_report_episode_cache as episode,
    (
     SELECT air1.* from ac_report_airing_cache air1
     INNER JOIN 
       (SELECT episode_id, min(start_time) as premiere_start 
        FROM ac_report_airing_cache
        GROUP BY episode_id) air2
     ON air1.episode_id=air2.episode_id
     WHERE air2.premiere_start = air1.start_time
     ) as airing_info
     SET episode.premiere_channel = airing_info.channel
     WHERE episode.episode_id = airing_info.episode_id
   ;";

  $sql .= "END ";

  db_query($sql);
}

function ac_report_recreate_airing_stored_procedure($db){
  $object  = 'airing';

  $procedure_name = "ac_import_".$object;
  $table_name = "ac_report_".$object."_cache";

  $sql = "DROP PROCEDURE IF EXISTS ".$procedure_name;
  db_query($sql);
  $sql = "CREATE PROCEDURE ".$procedure_name."()".
    " BEGIN ".
    "  TRUNCATE $table_name; ";

  $fields = array(
		  'airing_id',
		  'episode_id',
		  'project_id',
		  'title',
		  'created',
		  'changed',
		  'duration',
		  'start_time', 
		  'end_time', 
		  'channel',
		  );
  $fieldlist_parens = "( ". implode(', ', $fields) ." )";
  $sql .= "
   INSERT INTO $table_name $fieldlist_parens

   SELECT a.airing_id, s.field_airing_show_ref_target_id, 
     p.field_airing_project_ref_target_id, t.field_airing_title_value,
     FROM_UNIXTIME(a.created), FROM_UNIXTIME(a.changed),
     (UNIX_TIMESTAMP(dt.field_airing_date_value2) -
      UNIX_TIMESTAMP(dt.field_airing_date_value)), 
     dt.field_airing_date_value, dt.field_airing_date_value2, 
     c.field_airing_channel_tid
   FROM $db.cm_airing a 
   LEFT JOIN $db.field_data_field_airing_title t ON t.entity_id=a.airing_id
   LEFT JOIN $db.field_data_field_airing_channel c ON c.entity_id=a.airing_id
   LEFT JOIN $db.field_data_field_airing_date dt ON dt.entity_id=a.airing_id
   LEFT JOIN $db.field_data_field_airing_show_ref s ON s.entity_id=a.airing_id
   LEFT JOIN $db.field_data_field_airing_project_ref p
    ON p.entity_id=a.airing_id


   ;";
  $taxonomy_fields = array(		  
		  'channel', 
		  );

  foreach($taxonomy_fields as $tfield) {
    $sql .= "
      UPDATE $table_name t
      INNER JOIN $db.taxonomy_term_data td on td.tid = t.$tfield
      SET t.$tfield = td.name
    ;";
  }



  $sql .= "END ";
  db_query($sql);
}
function ac_report_recreate_producer_certification_stored_procedure($db){
  $sql = "DROP PROCEDURE IF EXISTS ac_import_producer_certification";
  db_query($sql);
  
  $sql = "CREATE PROCEDURE ac_import_producer_certification() ".
    " BEGIN ".
    "  TRUNCATE ac_report_producer_certification_cache; ";

  $sql .= "END ";
  db_query($sql);
}
function ac_report_recreate_producer_project_stored_procedure($db){
  $object  = 'producer_project';

  $procedure_name = "ac_import_".$object;
  $table_name = "ac_report_".$object."_cache";
  $fields = array(
		  'producer_id',
		  'project_id',
		  'type',
		  );
  $fieldlist_parens = "( ". implode(', ', $fields) ." )";



  $sql = "DROP PROCEDURE IF EXISTS ".$procedure_name;
  db_query($sql);

  $sql = "CREATE PROCEDURE ".$procedure_name."()".
    " BEGIN ".
    "  TRUNCATE $table_name; ";
   
  $sql .= "
    INSERT INTO $table_name $fieldlist_parens
    SELECT m.etid, m.gid, 'associative'
    FROM $db.node n
    INNER JOIN $db.og_membership m ON n.nid=m.gid
    WHERE n.type='cm_project' 
    AND m.entity_type='user'
  ;";

  $sql .= "
    UPDATE $table_name pp
    INNER JOIN ac_report_project_cache p USING(project_id)
    SET type = 'executive'
    WHERE p.exec_producer_id = pp.producer_id
  ;";

  $sql .= "UPDATE ac_report_producer_cache p " .
     "INNER JOIN " .
     "    (SELECT producer_id, count(1) as project_count " .
     "     FROM ac_report_producer_project_cache " .
     "     GROUP BY producer_id) as projects " .
     "  ON projects.producer_id=p.producer_id " .
     "SET p.number_of_projects = projects.project_count; ";
  
  $sql .= "END ";
  db_query($sql);
}


function ac_report_recreate_affiliate_org_stored_procedure($db){
  $object  = 'affiliate_org';

  $procedure_name = "ac_import_".$object;
  $table_name = "ac_report_".$object."_cache";

  $sql = "DROP PROCEDURE IF EXISTS ".$procedure_name;
  db_query($sql);
  $sql = "CREATE PROCEDURE ".$procedure_name."()".
    " BEGIN ".
    "  TRUNCATE $table_name; ";
  $sql .= "END ";
  db_query($sql);
}
function ac_report_recreate_producer_affiliate_org_stored_procedure($db){
  $object  = 'producer_affiliate_org';

  $procedure_name = "ac_import_".$object;
  $table_name = "ac_report_".$object."_cache";

  $sql = "DROP PROCEDURE IF EXISTS ".$procedure_name;
  db_query($sql);
  $sql = "CREATE PROCEDURE ".$procedure_name."()".
    " BEGIN ".
    "  TRUNCATE $table_name; ";
  $sql .= "END ";
  db_query($sql);
}


function ac_report_recreate_project_affiliate_org_stored_procedure($db){
  $object  = 'project_affiliate_org';

  $procedure_name = "ac_import_".$object;
  $table_name = "ac_report_".$object."_cache";

  $sql = "DROP PROCEDURE IF EXISTS ".$procedure_name;
  db_query($sql);
  $sql = "CREATE PROCEDURE ".$procedure_name."()".
    " BEGIN ".
    "  TRUNCATE $table_name; ";
  $sql .= "END ";
  db_query($sql);
}

function ac_report_recreate_producer_group_stored_procedure($db) {
  $object  = 'producer_group';

  $procedure_name = "ac_import_".$object;
  $table_name = "ac_report_".$object."_cache";

  $sql = "DROP PROCEDURE IF EXISTS ".$procedure_name;
  db_query($sql);
  $sql = "CREATE PROCEDURE ".$procedure_name."()".
    " BEGIN ".
    "  TRUNCATE $table_name; ";
  $sql .= "END ";
  db_query($sql);
} 

function ac_report_recreate_affiliate_org_group_stored_procedure($db) {
  $object  = 'affiliate_org_group';

  $procedure_name = "ac_import_".$object;
  $table_name = "ac_report_".$object."_cache";

  $sql = "DROP PROCEDURE IF EXISTS ".$procedure_name;
  db_query($sql);
  $sql = "CREATE PROCEDURE ".$procedure_name."()".
    " BEGIN ".
    "  TRUNCATE $table_name; ";
  $sql .= "END ";
  db_query($sql);
}

function ac_report_recreate_affiliate_org_tag_stored_procedure($db) {
  $object  = 'affiliate_org_tag';

  $procedure_name = "ac_import_".$object;
  $table_name = "ac_report_".$object."_cache";

  $sql = "DROP PROCEDURE IF EXISTS ".$procedure_name;
  db_query($sql);
  $sql = "CREATE PROCEDURE ".$procedure_name."()".
    " BEGIN ".
    "  TRUNCATE $table_name; ";
  $sql .= "END ";
  db_query($sql);
}
  
function ac_report_recreate_affiliate_org_category_stored_procedure($db) {
  $object  = 'affiliate_org_category';

  $procedure_name = "ac_import_".$object;
  $table_name = "ac_report_".$object."_cache";

  $sql = "DROP PROCEDURE IF EXISTS ".$procedure_name;
  db_query($sql);
  $sql = "CREATE PROCEDURE ".$procedure_name."()".
    " BEGIN ".
    "  TRUNCATE $table_name; ";
  $sql .= "END ";
  db_query($sql);
}

  
function ac_report_recreate_affiliate_org_verification_stored_procedure($db) {
  $object  = 'affiliate_org_verification';

  $procedure_name = "ac_import_".$object;
  $table_name = "ac_report_".$object."_cache";

  $sql = "DROP PROCEDURE IF EXISTS ".$procedure_name;
  db_query($sql);
  $sql = "CREATE PROCEDURE ".$procedure_name."()".
    " BEGIN ".
    "  TRUNCATE $table_name; ";
  $sql .= "END ";
  db_query($sql);
}
