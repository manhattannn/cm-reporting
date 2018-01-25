<?
/*
 * Created on Feb 2, 2010
 * Created by Mark Libkuman
 * libkuman@openflows.com
 * www.openflows.com
 * 
 * Created for Manhattan Neighborhood Network
 */
function ac_report_civi_db($db) {
  $db_array = array(
		    'cmtestingdrupal'=>'cmtestingcivi',
		    'cm_drupal'=> 'cm_civicrm_new',
		    );

  return $db_array[$db];
}

function ac_report_synch_form() {
 
  $form['box'] = array(
    '#type' => 'fieldset',
    '#title' => t('Synch Configuration'),
    '#prefix' => '<div id="synch-configuration-wrapper">', // This is our wrapper div.
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );
  $form['box']['header'] = array(
    '#value' => t("Configure options below and hit synch."),
    '#suffix' => "<br/>",
  );
  
   $form['box']['source_db'] = array(
    '#type' => 'textfield',
    '#title' => t('Source Database'),
    '#size' => 30,
    '#maxlength' => 64,
    '#description' => t('Enter name of source db in format: ').
      '<i>database_name@host</i> '.t('Note, if you change the source db ' .
          'you will need to recreate the stored procedures.'),
    '#default_value' => 'cm_drupal_new@192.168.209.123',
  );
  
  $options = array(
    'recreate' => t('Recreate Cache Tables'), 
    'truncate' => t('Truncate Existing Cache Tables'));
 
  $form['box']['cache_tables'] = array(
    '#type' => 'radios',
    '#title' => t('Cache Tables'),
    '#default_value' =>  'truncate',
    '#options' => $options,
  );
  
  $options = array(
    'recreate' => t('Recreate Stored Procedures'), 
    'reuse' => t('Use Existing Stored Procedures'));
 
  $form['box']['stored_procedures'] = array(
    '#type' => 'radios',
    '#title' => t('Stored Procedures'),
    '#default_value' =>  'recreate',
    '#options' => $options,
    '#description' => t("Stored Procedures are used to take data from " .
        "the Source DB and populate the Cache tables. Only select Recreate " .
        "if the Stored Procedures have changed since the last time data " .
        "was synched.  "),
  );
  
  $form['box']['submit'] = array(
    '#type' => 'submit', 
    '#value' => t('Synch Reporting Data'),
  );
  return $form;
}

function ac_report_synch_form_validate($form, &$form_state) {
  $source_db = $form_state['values']['box']['source_db'];
  if (!strpos($source_db, '@192.168.209.123')) {
    form_error($form['box']['source_db'], t('At this time the Source Database' .
        ' can only be 192.168.209.123.'));  
    return;  
  }
  else {
    $host = '192.168.209.123';
    $db = substr($source_db, 0, strpos($source_db, '@192.168.209.123'));
  }
  if (!ac_report_is_readable_database($db)) {
    form_error($form['box']['source_db'], $db . t(' does not exist or is not ' .
        ' readable by the db user of this site.'));  
    return;  
  }
}


function ac_report_synch_form_submit($form, &$form_state) {
  $source_db = $form_state['values']['box']['source_db'];
  if (!strpos($source_db, '@192.168.209.123')) {
    //FIXME find way to query remote Databases
  }
  else {
    $host = '192.168.209.123';
    $db = substr($source_db, 0, strpos($source_db, '@192.168.209.123'));
  }
  $cache_table_action = $form_state['values']['box']['cache_tables'];
  
  $stored_procedure_action = 
    $form_state['values']['box']['stored_procedures'];
    
  if ($cache_table_action == 'truncate') {
    ac_report_truncate_cache_tables();
  }
  else {
    ac_report_drop_cache_tables();
    ac_report_recreate_cache_tables();
  }
  
  if ($stored_procedure_action == 'reuse') {
    ac_report_run_stored_procedures();
  }
  else {
    ac_report_recreate_stored_procedures($db);
    ac_report_run_stored_procedures();
  }
}