<?
/*
 * Created on Feb 2, 2010
 * Created by Mark Libkuman
 * libkuman@openflows.com
 * www.openflows.com
 * 
 * Created for Manhattan Neighborhood Network
 */



function ac_report_is_readable_database($db_name) {
  $sql = "show databases";
  $result = db_query($sql);
  while ($db = db_fetch_object($result)) {
    if ($db->Database == $db_name) {
      return true;
    }
  }
  return false;
}

function ac_report_qlog($query){

//  TODO: make this function trace work
//  $c = debug_backtrace();
//  $c = $caller[1]['function'];
//  drupal_set_message('function '.$c.':');

  $args = func_get_args();
  array_shift($args);
  $query = db_prefix_tables($query);
  if (isset($args[0]) and is_array($args[0])) { 
    $args = $args[0];
  }
  _db_query_callback($args, TRUE);
  $query = preg_replace_callback(DB_QUERY_REGEXP, '_db_query_callback', $query);
  dsm($query);
  return ($query);
}

//         FIXME:                    maybe un-hardcode this
function ac_report_affiliate_category($dbname = 'mnnstage'){
  $entity_id = 30;
  $results = db_query(
    "SELECT affiliate_org_category_id, affiliate_org_id, category ".
    "FROM {ac_report_affiliate_org_category_cache} ".
    "WHERE category IS NOT NULL AND category != ''
  ");

  while ($result = db_fetch_object($results)) {
    $arg_array = explode('', $result->category);
    $arg_array_no_empties = array();
    foreach ( $arg_array as $arg ) {
      if ( trim($arg) ) {
        $arg_array_no_empties[] = $arg;
      }
    }

    $first_category_id = array_shift($arg_array_no_empties);
    $get_category_sql =
      "SELECT label FROM $dbname.civicrm_custom_option ".
      "WHERE entity_id = %d ".
      "AND value = %d";

    $category_result = db_fetch_object(db_query($get_category_sql, $entity_id, $first_category_id));
    $category = $category_result->label;
    $update_sql =
      "UPDATE {ac_report_affiliate_org_category_cache} ".
      "SET category = '%s' ".
      "WHERE affiliate_org_category_id = %d ";

    db_query($update_sql, $category, $result->affiliate_org_category_id);

    $insert_sql =
      "INSERT INTO {ac_report_affiliate_org_category_cache} ".
      "(affiliate_org_id, category) ".
      "VALUES (%d, '%s')";

    foreach($arg_array_no_empties as $category_id) {
      $category_result = db_fetch_object(db_query($get_category_sql, $entity_id, $category_id));
      $category = $category_result->label;
      db_query($insert_sql, $result->affiliate_org_id, $category);
    }
  }
}
