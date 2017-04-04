<?
/*
 * Created on Feb 2, 2010
 * Created by Mark Libkuman
 * libkuman@openflows.com
 * www.openflows.com
 * 
 * Created for Manhattan Neighborhood Network
 */

function ac_report_menu() {
   $items['ac_report_synch'] = array(
      'type' => MENU_NORMAL_ITEM,
      'title' => 'Reporting Synch',
      'page callback' => 'drupal_get_form',
      'page arguments'   => array('ac_report_synch_form'),
      'access callback' => 'ac_report_synch_access',
      'access arguments' => array(),
      'weight' => -10,
      );
  return $items;
}

function ac_report_synch_access() {
  global $user;
  if ($user->uid) {
    return true;
  }
  return false;
}
