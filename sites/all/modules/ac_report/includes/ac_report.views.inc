<?
/*
 * Created on Feb 2, 2010
 * Created by Mark Libkuman
 * libkuman@openflows.com
 * www.openflows.com
 * 
 * Created for Manhattan Neighborhood Network
 */

  /**
   * THIS FUNCTION WILL:
   * 1. JOIN ANY SUBQUERIES AS EXTRA VIEW RELATIONSHIPS (for counts and extra filters)
   * 2. REBUILD THE $query WHERE CLAUSE AND ARGS (based on altered filters)
   */
  function ac_report_views_query_alter(&$view, &$query) {
    //dsm("view");
    //dsm($view);
    //dsm("query");
    //dsm($query);
    //dsm($_GET);

    $base_table = $query->base_table;  
    
    $should_alter_count_fields =  FALSE;
    $extra_form_values = ac_report_get_extra_form_values();
    if (count($extra_form_values) > 0) {
      $should_alter_count_fields =  TRUE;
    }
    ac_report_views_query_subqueries($query, $extra_form_values);

    //fill up special field arrays    
    $dropdown_ignore_fields = array();
    $checkbox_null_fields = array();
    $checkbox_fields = array();
    $date_popup_fields = array();
    $query_count_transforms = array();
    ac_report_views_query_config($base_table, $dropdown_ignore_fields, $checkbox_null_fields,  
      $checkbox_fields, $date_popup_fields, $query_count_transforms);
    $clause_info_array = ac_report_get_clause_info_array($query);
    //dsm($clause_info_array);
    $should_skip_next_clause = FALSE;
    $new_where_clauses = array();
    foreach($clause_info_array as $clause_index => $clause_info) {        
      //some date fields crunch teh clauses into one, so we remove
      //this clause and continue
      if ($should_skip_next_clause) {
        unset($clause_info_array[$clause_index]);
        $should_skip_next_clause = FALSE;
        continue;
      }
      if ($clause_info['type'] == 'number' && $should_alter_count_fields) {
        foreach($query_count_transforms as $orig_field => $new_field) {
          if (strpos($clause_info['clause'], $orig_field)) {
            $clause_info_array[$clause_index]['clause'] = str_replace("$base_table.$orig_field", $new_field,  $clause_info['clause']);  
          } 
        }
      }
      else if ($clause_info['type'] == 'string') {
        $first_arg = $clause_info['arg_array'][0];
        $second_arg = $clause_info['arg_array'][1];
        //Find if the arg for the clause is one we should suppress from the query (i.e. arg="any")
        if (!is_array($first_arg) && $dropdown_ignore_fields[$first_arg] && 
            $dropdown_ignore_fields[$first_arg] == $second_arg) {
          unset($clause_info_array[$clause_index]);
        }
        
        //find if the arg for the clause means changing the clause to look for null values
        if (!is_array($first_arg) && $checkbox_null_fields[$first_arg] && 
             $checkbox_null_fields[$first_arg] == $second_arg) {
          $clause_info_array[$clause_index]['clause'] = "%s is null";
        }
        //if if the clause is acting on a checkbox, if so grab values from GET and modify clause and args          
        if (!is_array($first_arg) && $checkbox_fields[$first_arg]) {
          if (is_array($_GET[$checkbox_fields[$first_arg]])) {
            $first_time = true;
            $checkbox_clause = "";
            $checkbox_args = array();
            foreach ($_GET[$checkbox_fields[$first_arg]] as $checkbox_field) {
              if ($first_time) {
                $first_time = false;
              }
              else {
                $checkbox_clause .= " OR ";
              }
              if ($checkbox_null_fields[$first_arg] == $checkbox_field) {
                $checkbox_clause .= "$first_arg is NULL ";
              } 
              else {
                $checkbox_clause .= "$first_arg = '%s' ";
                $checkbox_args[] = $checkbox_field;
              }
            }
            $clause_info_array[$clause_index]['clause'] = $checkbox_clause;
            $clause_info_array[$clause_index]['arg_array'] = $checkbox_args;
          }
          else {
            unset($clause_info_array[$clause_index]);
            continue;
          }
        }
        
        //handle date widget clauses and args
        if (!is_array($first_arg) && $date_popup_fields[$first_arg] ) {
          $tmp_date = null;
          if ($second_arg && !is_array($second_arg)) {
            $tmp_date = date('m-d-Y', strtotime($second_arg));  
          }
          
          $upper = $date_popup_fields[$first_arg]['upper'];
          $lower = $date_popup_fields[$first_arg]['lower'];
          if ($_GET[$lower]['date'] &&
             ($_GET[$lower]['date'] ==
              $_GET[$upper]['date'])) {
             $should_skip_next_clause = TRUE;
             $clause_info_array[$clause_index]['clause'] = "%s >= '%s' AND %s <= '%s'";
             $clause_info_array[$clause_index]['arg_array'][] = $first_arg;  
             $clause_info_array[$clause_index]['arg_array'][] = 
               str_replace('00:00:00', '23:59:59', $clause_info_array[$clause_index+1]['arg_array'][1]);
          }
          else if ($tmp_date && $_GET[$lower]['date'] == $tmp_date) {
            $clause_info_array[$clause_index]['clause'] = "%s >= '%s' ";
          }
          else if ($tmp_date && $_GET[$upper]['date'] == $tmp_date) {
           $clause_info_array[$clause_index]['clause'] = "%s <= '%s' ";
           $clause_info_array[$clause_index]['arg_array'][1] = 
             str_replace('00:00:00', '23:59:59', $second_arg);
          }
          else {
            unset($clause_info_array[$clause_index]);
             $should_skip_next_clause = TRUE;
          }
        }
      }
    }
    //dsm("modified clause info array");
    //dsm($clause_info_array);

    //REBUILD THE $query WHERE CLAUSE USING THE MODIFIED $clause_info_array   
    $query->where[0]['clauses'] = array();
    $query->where[0]['args'] = array();
    reset ($clause_info_array);
    foreach($clause_info_array as $clause_index => $clause_info) {
      $clause = $clause_info['clause'];
      $args = $clause_info['arg_array'];
      $query->add_where(0, $clause, $args);
    }
    if ((count($query->where[0]['clauses']) == 0) && (count($query->where[0]['args']) == 0)) {
      unset ($query->where[0]);
    }
    
    //if ($query->base_table = "ac_report_producer_cache"){
    //  dsm("finished altering query");
      //dsm($query);
      //ac_report_qlog($query->query(true), $query->get_where_args());     
      //ac_report_qlog($query->query(false), $query->get_where_args());
    //}  
  }
 
  /**
   * FUNCTION TAKES A SUBQUERY AND JOINS IT TO THE VIEWS QUERY VIA A RELATIONSHIP
   */
  function ac_report_join_subquery_to_view(&$query, $subquery, $base_table, $base_field,  
    $subquery_field, $subquery_alias, $type = NULL ) {
    if (!$type) {
      $type = "LEFT";
    }
    $join = new views_join();
    $join->construct( $subquery, $base_table, $base_field, $subquery_field , array(), $type );
    $query->add_relationship($subquery_alias, $join, $base_field);        
  }

  /**
   * FUNCTION TAKES THE VALUES FROM THE EXTRA FILTERS ADDED TO THE VIEW AND
   * ADDS THEM TO SUBQUERIES THAT ARE JOINED TO THE VIEW VIA A RELATIONSHIP
   */
  function ac_report_views_query_subqueries(&$query, &$extra_form_values) {
    //dsm($extra_form_values);   
    //dsm($query->fields);   
    $subquery_info_array = ac_report_views_subquery_config();
    $view_base_table = $query->base_table;
    $view_subqueries = $subquery_info_array[$view_base_table];
    if (is_array($view_subqueries)) {
      //dsm($view_subqueries);
      foreach ($view_subqueries as $k1 => $subquery_info) {
        $subquery_base_table = $subquery_info['subquery_base_table'];
        $subquery_alias = $subquery_info['subquery_alias'] ? $subquery_info['subquery_alias'] : '';          
        $subquery_join_field= $subquery_info['subquery_join_field'];
        $subquery_count_field= $subquery_info['subquery_count_field'];
        $join_type_switch_excludes = $subquery_info['join_type_switch_excludes'] ?
          $subquery_info['join_type_switch_excludes']:array();
        $join_type= $subquery_info['join_type'];
  
        $query_field_trigger = $subquery_info['subquery_triggers']['query_field'];
        $extra_form_value_triggers = $subquery_info['subquery_triggers']['extra_form_value_fields'];
        $query_always_join = $subquery_info['subquery_triggers']['always_join'];
        
        $skip_subquery = TRUE;
        if ($query_field_trigger && !$query->fields[$query_field_trigger]) {
          //since a query field was set on the subquery trigger, we skip this 
          //subquery since the query field doesn't exist in $query->fields
          continue;
        }
        $query_field = $query->fields[$query_field_trigger];
        $submitted_query_field_trigger_value = $_GET[$query_field['field']];
        if ($query_field_trigger && $submitted_query_field_trigger_value) {
          $query->fields[$query_field_trigger]["field"] = $subquery_count_field;
          $query->fields[$query_field_trigger]["table"] = $subquery_alias;
          $skip_subquery = false;
        }
        
        foreach ($extra_form_value_triggers as $k2 => $extra_form_value_trigger) {
          if ($extra_form_values[$extra_form_value_trigger]) {
            if ($join_type == 'conditional'  && 
                !(in_array($extra_form_value_trigger, $join_type_switch_excludes))) {
              $join_type = 'INNER';
            }
            //if the trigger exists in $extra_form_values then break out of loop
            //and continue to build the suqbquery
            $skip_subquery = false;
          }
        } 
        if ($skip_subquery && !$query_always_join) {
          continue;
        }
        
        //AFTER THIS POINT THE SUBQUERY WILL BE ADDED
        //dsm($subquery_info);
        
        $subquery = "(SELECT $subquery_base_table.$subquery_join_field as $subquery_join_field, count(1) as $subquery_count_field " .
          "FROM $subquery_base_table ";
        
        $extra_join_where_clause = '';
        foreach ($subquery_info['extra_joins'] as $k3 => $extra_join) {
          //dsm($extra_join);
          $join_table = $extra_join['join_table'];
          $join_field = $extra_join['join_field'];
          
          $skip_extra_join = TRUE;
          foreach ($extra_join['join_triggers'] as $k4 => $join_trigger) {
            if ($extra_form_values[$join_trigger]) {
              $skip_extra_join = FALSE;
              break;  
            }
          }
          if ($skip_extra_join) {
            continue;
          }
          $subquery .= "INNER JOIN $join_table ON $join_table.$join_field = $subquery_base_table.$join_field ";
          foreach ($extra_join['join_where_clauses'] as $k5 => $where_clause) {
            //dsm($where_clause);
            if ($where_clause['extra_form_value_field']) {
              $operator = $where_clause['operator']; 
              $join_subquery_field = $where_clause['subquery_field'];
              //dsm($join_subquery_field);
              $extra_form_value = $extra_form_values[$where_clause['extra_form_value_field']];
              if (is_array($extra_form_value)) {
                $extra_join_where_clause .= " AND (";
                $first_time = true;
                foreach ($extra_form_value as $checkbox_value) {
                  if ($first_time) {
                    $first_time = false;
                  }
                  else {
                    $extra_join_where_clause .= " OR ";
                  }
                  //FIXME REMOVE HARDCODING, ADD TO CONFIG ARRAY
                  if ($checkbox_value == 'non_nyc') {
                    $extra_join_where_clause .= $join_table.".".$join_subquery_field. " is null ";
                  }
                  else {
                    $extra_join_where_clause .= $join_table.".".$join_subquery_field." = '$checkbox_value' ";
                  }
                }
                $extra_join_where_clause .= ") ";
              }
              else {
                if ($extra_form_value && $operator == "like") {
                  $extra_form_value  =  "'%$extra_form_value%'";
                }
                else if ($extra_form_value) {
                  $extra_form_value =  "'$extra_form_value'";
                }
                if ($extra_form_value) {
                  $extra_join_where_clause .= " AND $join_table.$join_subquery_field $operator $extra_form_value ";
                  
                }
              }
            }
            
            //dsm($extra_join_where_clause);
          }
        } 
        foreach ($subquery_info['subquery_where'] as $k6 => $where_clause)  {
          //dsm($where_clause);
          $subquery_field = $where_clause['subquery_field'];
     
          if ($where_clause['static_value']) {
            $value = $where_clause['static_value'];
          } 
          else {   
            $value = $extra_form_values[$where_clause['extra_form_value_field']] ?
            $extra_form_values[$where_clause['extra_form_value_field']]:'';
          }
          
          $operator = $where_clause['operator'];
          if (is_array($value)) {
            if (count($value) == 0) {
              continue;
            }
            $subquery .= ($k6==0)? " WHERE ": " AND ";
            $subquery .= " (";
            $first_time = true;
            foreach ($value as $checkbox_value) {
              if ($first_time) {
                $first_time = false;
              }
              else {
                $subquery .= " OR ";
              }
              //FIXME REMOVE HARDCODING, ADD TO CONFIG ARRAY
              if ($checkbox_value == 'non_nyc') {
                $subquery .= $subquery_base_table.".".$subquery_field. " is null ";
              }
              else {
                $subquery .= $subquery_base_table.".".$subquery_field." = '$checkbox_value' ";
              }
            }
            $subquery .= ") ";
          }   
          else {   
            if ($value && $operator == "like") {
              $value  =  "%$value%";
            }
            
            if ($value) {
              $subquery .= ($k6==0)? " WHERE ": " AND ";
              $subquery .= $subquery_base_table.".".$subquery_field." ".
                $operator." '".$value."' ";
            }
            else if (!$where_clause['extra_form_value_field']) { 
              $subquery .= ($k6==0)? " WHERE ": " AND ";
              $subquery .= $subquery_base_table.".".$subquery_field." ".
                $operator." ";
            }
          }
        } 
        $subquery .= $extra_join_where_clause;
        
        
        $subquery .= "GROUP BY $subquery_join_field) as";
        if ($join_type == 'conditional') {
          $join_type = 'LEFT';
        }
        ac_report_join_subquery_to_view($query, $subquery, $view_base_table, $subquery_join_field,  
          $subquery_join_field, $subquery_alias , $join_type);    
      }
    }
  } 
  
  /**
   * FUNCTION TAKES THE WHERE CLAUSE FROM THE QUERY OBJECT AND STORES IT IN AN
   * ARRAY SO THAT THE CLAUSES AND ARGS CAN BE LINKED TO ALLOW MODIDFICATION
   */
  function ac_report_get_clause_info_array(&$query) {
    $clause_info_array = array();
    foreach($query->where as $where_index => $where) {
      $query_arg_array = $query->where[$where_index]['args'];
      //Modify the where's clauses and args based on custom view form fields
      foreach($where['clauses'] as $tmp_clause_index=>$tmp_clause) {
        $argnumber_count = substr_count($tmp_clause, '%d');
        $argstring_count = substr_count($tmp_clause, '%s');
        $new_arg_array = array();
        if ($argnumber_count > 0 and $argstring_count > 0) {
          drupal_set_message("ERROR CODE 34399: View field not expecting mismatched arg types");
        }
        if ($argnumber_count) {
          $clause_type = "number";
        }
        else if ($argstring_count) {
          $clause_type = "string";
        }
        for($i=0; $i < ($argnumber_count + $argstring_count); $i++ ) {
          $new_arg_array[] = array_shift($query_arg_array);
        }
        $clause_info_array[] = array(
          'type' => $clause_type,
          'clause' => $tmp_clause,
          'arg_array' => $new_arg_array,
        );
      } 
    }    
    return $clause_info_array;
  }
  
  /**
   * FUNCTION CREATES VIEW HEADERS. IT IS CALLED FROM THE VIEW INTERFACE 
   * VIA THE CUSTOM PHP INPUT FILTER OF THE VIEW HEADER 
   */
  function ac_report_get_views_header() {
    $view = views_get_current_view();

    $full_query = 
      str_replace('{','',str_replace('}', '', $view->build_info['query']));


    $count_query = $view->build_info['count_query'];
    $select_less_query =substr($count_query, strpos($count_query, "FROM")); 
    $query_args = $view->build_info['query_args'];

    //dsm($view);
    //dsm($view->current_display);
    //dsm($view->base_field);
    //dsm($view->build_info);
    if ($view->base_field == 'item_reservation_id') {
      $results = db_query("SELECT COUNT(distinct ac_report_item_reservation_cache.producer_id) as producers, " .
                         "       COUNT(distinct ac_report_item_reservation_cache.project_id) as projects, " .
                         "       COUNT(distinct ac_report_item_reservation_cache.affiliate_org_id) as affiliates,".
                         "       SUM(reserve_length) as hours " .
                         $select_less_query, $query_args);
      $result = db_fetch_object($results);
      
      $count = $view->total_rows;
      $unique_producers = $result->producers;
      $unique_projects = $result->projects;
      $affiliates = $result->affiliates ? $result->affiliates : 0;
      $hours = $result->hours;
      if (!$hours) {
        $hours = 0;
        $average = 0;
      }
      else {
        $hours = $hours/(60*60);
        $average = $hours/$count;
      }
      
      return "<br/>" .
              "<table>" .
              "<th>Total Results</th><th>Unique Producers</th>" .
              "<th>Unique Projects</th><th>Total Hours</th>" .
              "<th>Hours Per Use</th><th>Total Affiliates</th>" .
              "<tr><td>$count</td><td>$unique_producers</td><td>$unique_projects</td><td>$hours</td>" .
              "<td>$average</td><td>$affiliates</td></tr></table><br/>";            
      }
      else if ($view->base_field == 'episode_id'){
        
        $results = db_query("SELECT COUNT(distinct ac_report_episode_cache.exec_producer_id ) as producers, " .
                         "       COUNT(distinct ac_report_episode_cache.project_id) as projects, " .
                         "       SUM(duration) as seconds, SUM(duration*number_of_airings) as airtime " .
                           $select_less_query, $query_args);
       $result = db_fetch_object($results);
        
        $count = $view->total_rows;
        $unique_producers = $result->producers;
        $unique_projects = $result->projects;
        $seconds = $result->seconds;
        $airtime = $result->airtime;
        
        if (!$seconds) {
          $hours = 0;
          $average = 0;
        }
        else {
          $hours = $seconds/(60*60);
          $average = ($seconds/60)/$count;
        }
        if (!$airtime) {
          $airtime = 0;
        }
        else {
          $airtime = $airtime/(60*60);
        }
        
        return "<br/>" .
                "<table>" .
                "<th>Total Results</th><th>Unique Producers</th><th>Unique Projects</th>" .
                "<th>Total Hours</th><th>Total Air Hours</th><th>Minutes Per Episode</th>" .
                "<tr><td>$count</td><td>$unique_producers</td><td>$unique_projects</td><td>$hours</td>" .
                "<td>$airtime</td><td>$average</td></tr></table><br/>";     
      }
    ////////////////////////////////////////////////////////////////////////
    //PRODUCER CLASS REPORT
    else if ($view->base_field == 'class_producer_id'){
      $results = db_query(
        "SELECT COUNT(distinct ac_report_producer_class_cache.producer_id) as producers, " .
        "COUNT(distinct ac_report_producer_class_cache.contact_id) as contacts, " .
	"COUNT(distinct ac_report_producer_class_cache.class_id ) as classes," .
	"COUNT(distinct ac_report_class_cache_ac_report_producer_class_cache.course_title) ".
	"  as courses, " .
	"COUNT(distinct ac_report_producer_class_cache.affiliate_org_id) as affiliates,".
	"SUM(session_hours) as seconds ".
	$select_less_query, $query_args);
      
      $result = db_fetch_object($results);
        
      $count = $view->total_rows;
      $unique_producers = $result->producers;
      $unique_contacts = $result->contacts;
      $classes = $result->classes;
      $courses = $result->courses;
      $seconds = $result->seconds;
      $affiliates = $result->affiliates ? $result->affiliates : 0;
      
      if (!$seconds) {
	$hours = 0;
	$average = 0;
      }
      else {
	$hours = $seconds;
	$average = ($hours)/$count;
      }

      return "<br/>" .
	"<table>" .
	"<th>Total Results</th><th>Unique Producers</th><th>Unique People</th>" .
	"<th>Total Courses</th><th>Total Classes</th><th>Total Hours</th>".
	"<th>Hours Per Class</th><th>Total Affiliate Orgs</th><tr><td>$count</td>".
	"<td>$unique_producers</td><td>$unique_contacts</td><td>$courses</td>".
	"<td>$classes</td><td>$hours</td><td>$average</td><td>$affiliates</td>".
	"</tr></table><br/>";     
    }
    /////////////////////////////////////////////////////////////////
    //PRODUCER HEADER
    /////////////////////////////////////////////////////////////////
    else if ($view->base_field == 'producer_id') {
      $classes_field = (strpos($count_query, "class_count") > 0) ? 
        "producer_classes.class_count" : "ac_report_producer_cache.number_of_classes";
        
      $projects_field = (strpos($count_query, "project_count") > 0) ? 
        "producer_projects.project_count" : "ac_report_producer_cache.number_of_projects";
        
      $episodes_field = (strpos($count_query, "episode_count") > 0) ? 
        "producer_episodes.episode_count" : "ac_report_producer_cache.number_of_episodes";
        
      $reservations_field = (strpos($count_query, "reservation_count") > 0) ? 
        "producer_reservations.reservation_count" : "ac_report_producer_cache.number_of_reservations";
        
      $affiliates_field = (strpos($count_query, "affiliate_count") > 0) ? 
        "producer_affiliates.affiliate_count" : "ac_report_producer_cache.number_of_affiliates";
            
      $results = db_query(
          "SELECT  SUM($classes_field) as classes, ".
          "        SUM($projects_field) as projects, ".
          "        SUM($episodes_field) as episodes, ".
          "        SUM($reservations_field) as reservations, ".
          "        SUM($affiliates_field) as affiliates ".
          $select_less_query, $query_args);
           
      $result = db_fetch_object($results);
      $count = $view->total_rows ? $view->total_rows: 0;
      $classes = $result->classes ? $result->classes: 0;
      $episodes = $result->episodes ? $result->episodes: 0;
      $projects = $result->projects ? $result->projects: 0;
      $reservations = $result->reservations ? $result->reservations: 0;
      $affiliates = $result->affiliates ? $result->affiliates: 0;
      $activities = $classes + $episodes + $projects + $reservations;  
        
      return "<br/>" .
              "<table>" .
              "<th>Total Producers</th><th>Total Class Enrollments</th>" .
              "<th>Total Executive Produced Episodes</th><th>Total Project Memberships</th>" .
              "<th>Total Reservations</th><th>Total Activities (Class+Ep+Proj+Res)</th>" .
              "<th>Total Affiliate Org Relationships</th>" .
              "<tr><td>$count</td><td>$classes</td>" .
              "<td>$episodes</td><td>$projects</td>" .
              "<td>$reservations</td><td>$activities</td>" .
              "<td>$affiliates</td></tr></table><br/>";     
    } 
    else if ($view->base_field == 'project_id') {
      $producers_field = "ac_report_project_cache.exec_producer_id";
        
      $episodes_field = (strpos($count_query, "episode_count") > 0) ? 
        "project_episodes.episode_count" : "ac_report_project_cache.number_of_episodes";
        
      $reservations_field = (strpos($count_query, "reservation_count") > 0) ? 
        "project_reservations.reservation_count" : "ac_report_project_cache.number_of_reservations";
        
      $affiliates_field = (strpos($count_query, "affiliate_count") > 0) ? 
        "project_affiliates.affiliate_count" : "ac_report_project_cache.number_of_affiliates";
        
      
      $total_producers_field = (strpos($count_query, "total_producer_count") > 0) ? 
        "project_producers.total_producer_count" : "ac_report_project_cache.number_of_producers";
        
      $results = db_query(
        "SELECT  COUNT(distinct $producers_field) as producers, ".
        "        SUM($total_producers_field) as total_producers, ".
        "        SUM($episodes_field) as episodes, " .
        "        SUM($reservations_field) as reservations, " .
        "        SUM($affiliates_field) as affiliates ".
                         $select_less_query, $query_args);
      $result = db_fetch_object($results);
                         
      $count = $view->total_rows ? $view->total_rows: 0;
      $producers = $result->producers ? $result->producers: 0;
      $total_producers = $result->total_producers ? $result->total_producers: 0;
      $episodes = $result->episodes ? $result->episodes: 0;
      $reservations = $result->reservations ? $result->reservations: 0;
      $affiliates = $result->affiliates ? $result->affiliates: 0;
      $activities = $episodes + $reservations;  
        
      return "<br/>" .
            "<table>" .
            "<th>Total Projects</th>" .
            "<th>Total Unique Executive Producers</th>" .
            "<th>Total Project Members</th>".
            "<th>Total Episodes</th>" .
            "<th>Total Reservations</th>" .
            "<th>Total Activities (Ep+Res)</th>" .
            "<th>Total Affiliate Orgs</th>" .
            "<tr><td>$count</td>" .
            "<td>$producers</td>" .
            "<td>$total_producers</td>" .
            "<td>$episodes</td>" .
            "<td>$reservations</td>" .
            "<td>$activities</td>" .
            "<td>$affiliates</td></tr></table><br/>";     
    } 
    else if ($view->base_field == 'item_id') {
      $bucket_category_count = count($_GET['bucket_category']);
    //dsm($view);
    //dsm($view->current_display);
    //dsm($view->base_field);
    //dsm($view->build_info);

      $header = array(t('Name'), t('Items'), t('Buckets'), t('Reservations')); 
      $rows = array();
      if ( $bucket_category_count > 1 ) {
        foreach ( $_GET['bucket_category'] as $k => $category ) {
          $subquery_args = array();
          for ( $i = 0; $i < $bucket_category_count ; $i++ ) {
            $subquery_args[$i] = $category;
          }
          $sub_results = db_query(
               "SELECT  COUNT(*) as total_subitems, COUNT(distinct ac_report_item_cache.bucket_id) as buckets," .
               "        SUM(reservation_count) as reservations  ".
                                $select_less_query, $subquery_args);
          $values = db_fetch_object($sub_results);
          $rows[] = array($category, $values->total_subitems, $values->buckets, $values->reservations ? $values->reservations : 0);
        }
      }
    
      $results = db_query(
           "SELECT  COUNT(distinct ac_report_item_cache.bucket_id) as buckets," .
           "        SUM(reservation_count) as reservations  ".
                            $select_less_query, $query_args);
      $result = db_fetch_object($results);
       
      $count = $view->total_rows;
      $buckets = $result->buckets;
      if (!$buckets) {
        $buckets = 0;
      }
      
      $reservations = $result->reservations ? $result->reservations: 0;  
      if ( count($rows) ) {
        $rows[] = array('<strong>'.t('Totals').'</strong>', $count, $buckets, $reservations);
        return theme('table', $header, $rows);
      }
      else {
        return "<br/>" .
             "<table>" .
             "<th>Total Items</th><th>Total Buckets</th><th>Total Reservations</th>" .
             "<tr><td>$count</td>" .
             "<td>$buckets</td><td>$reservations</td></tr></table><br/>";    
      }
    }
    else if ($view->base_field == 'affiliate_org_id') {
      $producers_field = (strpos($count_query, "producer_count") > 0) ? 
        "affiliate_org_producers.producer_count" : "ac_report_affiliate_org_cache.number_of_producers";
      
      $projects_field = (strpos($count_query, "project_count") > 0) ? 
        "affiliate_org_projects.project_count" : "ac_report_affiliate_org_cache.number_of_projects";

      $classes_field = (strpos($count_query, "class_count") > 0) ? 
        "affiliate_org_classes.class_count" : "ac_report_affiliate_org_cache.number_of_classes";
        
      $episodes_field = (strpos($count_query, "episode_count") > 0) ? 
        "affiliate_org_episodes.episode_count" : "ac_report_affiliate_org_cache.number_of_episodes";
        
      $reservations_field = (strpos($count_query, "reservation_count") > 0) ? 
        "affiliate_org_reservations.reservation_count" : "ac_report_affiliate_org_cache.number_of_reservations";
        
      $header_sql = 
        "SELECT  SUM($producers_field) as producers, ".
        "        SUM($projects_field) as projects, " .
        "        SUM($classes_field) as classes, " .
        "        SUM($episodes_field) as episodes, " .
        "        SUM($reservations_field) as reservations " .
        $select_less_query;
      
      $results = db_query($header_sql,  $query_args);
                        
      $result = db_fetch_object($results);
      $count = $view->total_rows ? $view->total_rows: 0;
      $producers = $result->producers ? $result->producers: 0;
      $projects = $result->projects ? $result->projects: 0;
      $classes = $result->classes ? $result->classes: 0;
      $episodes = $result->episodes ? $result->episodes: 0;
      $reservations = $result->reservations ? $result->reservations: 0;
      $activities = $classes + $episodes + $projects + $reservations;  
      
                         
      return "<br/>" .
            "<table>" .
            "<th>Total Affiliate Orgs</th>" .
            "<th>Total Producers</th>" .
            "<th>Total Projects</th>" .
            "<th>Total Class Enrollment</th>" .
            "<th>Total Episodes</th>" .
            "<th>Total Reservations</th>" .
            "<th>Total Activities (Proj+Class+Ep+Res)</th>" .
            "<tr><td>$count</td>" .
            "<td>$producers</td>" .
            "<td>$projects</td>" .
            "<td>$classes</td>" .
            "<td>$episodes</td>" .
            "<td>$reservations</td>" .
            "<td>$activities</td>" .
            "</tr></table><br/>";     
    }
    
    else if ($view->base_field == 'class_id') {
      $header_sql = 
        "SELECT  SUM(number_of_sessions) as sessions, ".
        "        COUNT(distinct primary_trainer_name) as trainers, " .
        "        COUNT(distinct certification) as certifications, " .
        "        SUM(number_attended) as attended, " .
        "        SUM(session_hours) as session_hours, " .
        "        COUNT(distinct ac_report_class_cache.affiliate_org_id) as affiliates " .
        $select_less_query;

      $results = db_query($header_sql,  $query_args);
                        
      $result = db_fetch_object($results);
      $count = $view->total_rows ? $view->total_rows: 0;
      $sessions = $result->sessions ? $result->sessions: 0;
      $trainers = $result->trainers ? $result->trainers: 0;
      $certifications = $result->certifications ? $result->certifications: 0;

      $session_hours = $result->session_hours ? $result->session_hours: 0;
      $affiliates = $result->affiliates ? $result->affiliates: 0;

      $classes_sql =
	"SELECT class_id, number_attended, number_producer_students ". $select_less_query;
      
      $results = db_query($classes_sql,  $query_args);

      $attended = 0;
      while ($result = db_fetch_object($results)) {
	if ($result->number_attended &&
	    ($result->number_attended >= $result->number_producer_students)) {
	  $attended += $result->number_attended;
	}
	else if ($result->number_producer_students) {
	  $attended += $result->number_producer_students;
	}	
      }
                         
      return "<br/>" .
            "<table>" .
            "<th>Total Classes</th>" .
            "<th>Total Number Of Sessions</th>" .
            "<th>Total Trainers</th>" .
            "<th>Total Certifications</th>" .
            "<th>Total Number of Attended</th>" .
            "<th>Total Session Hours</th>" .
            "<th>Total Affiliate Orgs (not affiliate locations)</th>" .
            "<tr><td>$count</td>" .
            "<td>$sessions</td>" .
            "<td>$trainers</td>" .
            "<td>$certifications</td>" .
            "<td>$attended</td>" .
            "<td>$session_hours</td>" .
            "<td>$affiliates</td>" .
            "</tr></table><br/>";     
    }
    
    else if ($view->base_field == 'trainer_class_id') {
       $header_sql = 
        "SELECT  COUNT(distinct ac_report_producer_cache_ac_report_trainer_class_cache.producer_id) as trainers, ".
        "        COUNT(distinct certification) as certifications, " .
        "        COUNT(distinct course_title) as courses, " .
        "        COUNT(distinct ac_report_trainer_class_cache.class_id ) as classes, " .
        "        SUM(number_producer_students) as passed_failed, " .
        "        SUM(number_attended) as attended, " .
        "        COUNT(distinct affiliate_org_id) as affiliates " .
        $select_less_query;

      $results = db_query($header_sql,  $query_args);
                        
      $result = db_fetch_object($results);
      $count = $view->total_rows ? $view->total_rows: 0;
      $trainers = $result->trainers ? $result->trainers: 0;
      $classes = $result->classes ? $result->classes: 0;
      $courses = $result->courses ? $result->courses: 0;
      $certifications = $result->certifications ? $result->certifications: 0;
      $passed_failed = $result->passed_failed ? $result->passed_failed: 0;
      $attended = $result->attended ? $result->attended: 0;
      $affiliates = $result->affiliates ? $result->affiliates: 0;
      
      $producer_class_status_sql = 
        "SELECT count(status) as status_count, status as name " .
        "FROM ac_report_producer_class_cache " .
        "WHERE class_id IN " .
        "  (SELECT ac_report_class_cache_ac_report_trainer_class_cache.class_id " .
        "   $select_less_query)" .
        "GROUP BY status " .
        "ORDER BY " .
        "status='passed'," .
        "status='failed'," .
        "status='enrolled'," .
        "status='confirmed'," .
        "status='waitlist'," .
        "status='cancelled'," .
        "status='unconfirmed'";
    
      $enrolled_count = 0;
      $status_results = db_query($producer_class_status_sql,  $query_args);
      
      //ac_report_qlog($producer_class_status_sql, $query_args);
    
      while ($status = db_fetch_object($status_results)){
        $status_counts .= $status->name . ": ". $status->status_count . "<br/>";
        if ($status->name == 'passed') {
          $passed_count += $status->status_count;
        }
        if ($status->name == 'failed') {
          $failed_count += $status->status_count;
        }
        $enrolled_count += $status->status_count;
      }
      $status_counts .= "total: $enrolled_count";
                         
      $ret =  "<br/>" .
            "<table>" .
            "<th>Total Results</th>" .
            "<th>Unique Trainers</th>" .
            "<th>Unique Classes</th>" .
            "<th>Unique Courses</th>" .
            "<th>Unique Certifications</th>" .
            "<th>Total Attended (Used by YC/CM)</th>" .
            "<th>Total Passed/Failed</th>" .
            "<th>Enrollment Status Counts</th>" .
            "<th>Unique Affiliate Orgs</th>" .
            "<tr valign='top'><td>$count</td>" .
            "<td>$trainers</td>" .
            "<td>$classes</td>" .
            "<td>$courses</td>" .
            "<td>$certifications</td>" .
            "<td>$attended</td>" .
            "<td>".($passed_count + $failed_count)."</td>" .
            "<td nowrap>$status_counts</td>" .
            "<td>$affiliates</td>" .
            "</tr></table><br/>";  
            
      
              
      return $ret;   
    }
    ////////////////////////////////////////////////////////////////////////////////
    //CHANNEL REPORT
    ///////////////////////////////////////////////////////////////////////////////
    else if ($view->base_field == 'airing_id') {
      $group_by_channel_sql =
	"SELECT channel, ".
	"COUNT(distinct ac_report_airing_cache.episode_id) as episodes, ".
	"SUM(ac_report_airing_cache.duration) as runtime, ".
	"COUNT(ac_report_airing_cache.airing_id) as total_runs " .
	"FROM ac_report_airing_cache " .
	"WHERE airing_id IN " .
	"  (SELECT ac_report_airing_cache.airing_id " .
	"   $select_less_query)" .
	"GROUP BY channel " .
	"ORDER BY channel";
      
      $channel_results = db_query($group_by_channel_sql,  $query_args);
      $ret =  "<br/>" .
	"<table>" .
	"<th>Channel</th>" .
	"<th>Unique Shows</th>" .
	"<th>Total Airings</th>" .
	"<th>Total Runtime in Hours</th>";
      
      while ($channel = db_fetch_object($channel_results)){
	$ret .= 
	  "<tr valign='top'>" .
	  "<td>" .$channel->channel ."</td>" .
	  "<td>" .$channel->episodes ."</td>" .
	  "<td>" .$channel->total_runs ."</td>" .
	  "<td>" .number_format((float)($channel->runtime/(60*60)), 2, '.', '') ."</td>" .
	  "</tr>";	 
       }
      
      $ret .= "</table><br/>";
      
      return $ret;   
    }
  }

  
 
