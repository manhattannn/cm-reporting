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
 * ALTERS THE VIEWS FILTERS VIA THE FORM API
 */
function ac_report_form_alter(&$form, &$form_state, $form_id) {
  switch($form_id) {
    case 'views_exposed_form':
      $dropdown_fields = array();
      $checkbox_fields = array();   
      $date_fields = array();
      $additional_date_fields = array();
      $fieldsets = array();
      $additional_checkboxes = array();
      $additional_dropdowns = array();
      $additional_textfields = array();
    
      ac_report_views_filter_alter_form_config($form['#id'], $dropdown_fields,  
        $checkbox_fields, $date_fields, $fieldsets, $additional_date_fields, 
        $additional_checkboxes, $additional_dropdowns, $additional_textfields);   
      
      ac_report_views_filter_alter_dropdowns($form, $form_state, $dropdown_fields);
      ac_report_views_filter_alter_checkboxes($form, $checkbox_fields);
      if ( in_array('date_popup', module_list()) ) {
        ac_report_views_filter_alter_date_widget($form, $date_fields);
        ac_report_views_filter_extra_date_widgets($form, $additional_date_fields);
      }
      ac_report_views_filter_extra_fieldsets($form, $fieldsets);
      ac_report_views_filter_extra_checkboxes($form, $additional_checkboxes);
      ac_report_views_filter_extra_dropdowns($form, $additional_dropdowns);
      ac_report_views_filter_extra_textfields($form, $additional_textfields);
      
      $form['submit']['#weight'] = 10;
      break;      
    }
  }  
  
  /**
   * FUNCTION TAKES SIMPLE TEXTFIELDS FROM THE VIEW FORM AND TURNS THEM INTO
   * DROPDOWNS POPULATED WITH DISTINCT VALUES FROM THE CACHE TABLES 
   */
  function ac_report_views_filter_alter_dropdowns(&$form, &$form_state, &$dropdown_fields) {
    foreach($dropdown_fields as $field_name=>$get_function) { 
      if ($form[$field_name]['#type'] == 'textfield') {
        $field = &$form[$field_name];
        unset($field['#size']);
        $field['#type'] = "select";
        $field['#options'] = $get_function();
        unset($field['#value']);
        if ($form_state['input'][$field_name]) {
          $default = $form_state['input'][$field_name];
        }
        if (!is_array($form_state['input'])) {
          $form_state['input'] = array(
            $field_name => $default,
          );
        }
        else {
         $form_state['input'][$field_name] = $default;
        }
      }
    }
  }

  /**
   * FUNCTION TAKES SIMPLE TEXTFIELDS FROM THE VIEW FORM AND TURNS THEM INTO
   * CHECKBOXES POPULATED WITH DISTINCT VALUES FROM THE CACHE TABLES 
   */
  function ac_report_views_filter_alter_checkboxes(&$form, &$checkbox_fields ) {
    foreach($checkbox_fields as $field_name=>$get_function) { 
      if ($form[$field_name]['#type'] == 'textfield') {
        $field = &$form[$field_name];
        unset($field['#size']);
        $field['#type'] = "checkboxes";
        $field['#options'] = $get_function();
        $field['#value'] = null;
        unset($field['#default_value']);
      }
    }
  }
  
  
  /**
   * FUNCTION TAKES SIMPLE TEXTFIELDS FROM THE VIEW FORM AND TURNS THEM INTO
   * DATE WIDGETS
   */
  function ac_report_views_filter_alter_date_widget(&$form, & $date_fields) {
    foreach($date_fields as $field) {
      if ($form[$field]) {
        $form[$field]['#type'] = 'date_popup';
        $form[$field]['#date_year_range'] = '-25:+1' ;
      }  
    }                                       
  }

  /**
   * FUNCTION ADDS EXTRA DATE WIDGETS TO THE FILTERS TO USE IN SUBQUERIES ADDED
   * VIA VIEWS RELATIONSHIPS
   */
  function ac_report_views_filter_extra_date_widgets(&$form, &$additional_date_fields) {
    foreach($additional_date_fields as $field=>$title) {
      $form[$field]['#title'] = $title;
      $form[$field]['#type'] = 'date_popup';
      $form[$field]['#size'] = 30;
      $form[$field]['#date_year_range'] = '-25:+1' ;
    }     
  }
  /**
   * FUNCTION ADDS FIELDSETS TO GROUP THE EXTRA FILTER WIDGETS USED IN SUBQUERIES 
   * ADDED VIA VIEWS RELATIONSHIPS
   */
  function ac_report_views_filter_extra_fieldsets(&$form, &$fieldsets) {
    if (!is_array($fieldsets)) {
      return;
    }
    //dsm($fieldsets);
    foreach ($fieldsets as $field=>$title) {
      $form[$field] = array(
        '#title' => $title,
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
    }
  }

  /**
   * FUNCTION ADDS EXTRA CHECKBOXES TO THE FILTERS TO USE IN SUBQUERIES ADDED
   * VIA VIEWS RELATIONSHIPS
   */
  function ac_report_views_filter_extra_checkboxes(&$form, &$additional_checkboxes) {
    $extra_form_values = ac_report_get_extra_form_values();
    foreach($additional_checkboxes as $field_name=>$field_info) {
      $form[$field_info['fieldset']][$field_name] = array(
        '#title' =>  $field_info['title'],
        '#type' => 'checkboxes',
        '#options' => $field_info['options'],
      );
      if ($extra_form_values[$field_name]) {
        $form[$field_info['fieldset']]['#collapsed'] = FALSE;
      }
    }     
  }
  
  
  /**
   * FUNCTION ADDS EXTRA DROPDOWNS TO THE FILTERS TO USE IN SUBQUERIES ADDED
   * VIA VIEWS RELATIONSHIPS
   */
  function ac_report_views_filter_extra_dropdowns(&$form, &$additional_dropdowns) {
    $extra_form_values = ac_report_get_extra_form_values();
    foreach($additional_dropdowns as $field_name=>$field_info) {
      $form[$field_info['fieldset']][$field_name] = array(
        '#title' =>  $field_info['title'],
        '#type' => 'select',
        '#options' => $field_info['options'],
      );
      if ($extra_form_values[$field_name]) {
        $form[$field_info['fieldset']]['#collapsed'] = FALSE;
      }
    }     
  }
  
  /**
   * FUNCTION ADDS EXTRA DROPDOWNS TO THE FILTERS TO USE IN SUBQUERIES ADDED
   * VIA VIEWS RELATIONSHIPS
   */
  function ac_report_views_filter_extra_textfields(&$form, $additional_textfields) {
     $extra_form_values = ac_report_get_extra_form_values();
    foreach($additional_textfields as $field_name=>$field_info) {
      $form[$field_info['fieldset']][$field_name] = array(
        '#title' =>  $field_info['title'],
        '#type' => 'textfield',
      );
      if ($extra_form_values[$field_name]) {
        $form[$field_info['fieldset']]['#collapsed'] = FALSE;
      }
    }  
  }
  /**
   * GRABS THE VALUES OF THE FORM ELEMENTS WE ADDED TO THE VIEW FILTERS
   * FROM $_GET. IT EXCLUDES CHECKBOX VALUES OF "any" AND STORES DATES
   * IN THE EXPECTED FORMAT     
   */
  function ac_report_get_extra_form_values(){
    global $ac_report_views_extra_form_values;
    if ($ac_report_views_extra_form_values) {
      return $ac_report_views_extra_form_values;
    }
    $ac_report_views_extra_form_values = array();
    
    foreach($_GET as $key => $value) {
      if (strpos($key, "checkboxes") > 0) {
        if ($value && is_array($value) && (count($value) > 0)){
          $ac_report_views_extra_form_values[$key] = $value; 
        }
      }
      if (strpos($key, "dropdown") > 0) {
        if ($value && $value != 'any') {
          $ac_report_views_extra_form_values[$key] = $value; 
        }
      }
      if (strpos($key, "textfield") > 0) {
        if ($value) {
          $ac_report_views_extra_form_values[$key] = $value; 
        }
      }
      if (strpos($key, "min_date") > 0) {
        if ($value['date']) {
          $min_date_array = explode("-", $value['date']);
          $ac_report_views_extra_form_values[$key] = 
            "$min_date_array[2]-$min_date_array[0]-$min_date_array[1]";
        }
      }
      if (strpos($key, "max_date") > 0) {
        if ($value['date']) {
          $max_date_array = explode("-", $value['date']);
          $ac_report_views_extra_form_values[$key] = 
            "$max_date_array[2]-$max_date_array[0]-$max_date_array[1] " .
            "23:59:59";
        }
      }
    }
    //dsm($ac_report_views_extra_form_values);
    return $ac_report_views_extra_form_values;
  }
   