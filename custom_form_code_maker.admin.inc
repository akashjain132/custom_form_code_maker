<?php

/**
 * @file
 * Have some functions used in custom form code maker.
 */

function custom_form_code_maker() {

  // Load file which include ajax callback definition.
  module_load_include('inc', 'custom_form_code_maker', 'custom_form_code_maker.support');

  drupal_add_js(drupal_get_path('module', 'custom_form_code_maker') . '/js/custom_form_code_maker.js');
  // drupal_add_css(drupal_get_path('module', 'custom_form_code_maker') . '/css/custom_form_code_maker.css');

  $form = drupal_get_form('get_form_name_and_field');

  return $form;
}

function get_form_name_and_field($form, &$form_state) {

  $form['#tree'] = TRUE;

  $form['form_name'] = array(
  	'#type' => 'textfield',
  	'#title' => t('Form Name'),
  	'#required' => TRUE,
  	'#access' => TRUE,
  	'#size' => 30,
  	'#attributes' => array(
  		'class' => array('form_name'),
  		'placeholder' => 'Enter Form Name',
  	),
    '#element_validate' => array('validate_form_function_name'),
  );

  $form['number_of_form_element'] = array(
  	'#type' => 'select',
  	'#title' => t('Number of form Element'),
  	'#required' => TRUE,
  	'#access' => TRUE,
  	'#options' => array_slice(range(0,10), 1, NULL, TRUE),
  	'#attributes' => array(
  		'class' => array('number_of_form_element'),
  	),
    '#ajax' => array(
      'event' => 'change',
      'callback' => 'show_form_elements',
      'wrapper' => 'chose-form-elements',
    ),
  );

  /* Ajax wrapper to show form element type name*/
  $form['chose_form_elements'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => 'chose-form-elements'),
  );

  if (isset($form_state['values']['number_of_form_element'])) {

    $number_of_elements     = $form_state['values']['number_of_form_element'];
    $form_element_type_name = variable_get('form_element_type_name', array());

    for ($i = 1; $i <= $number_of_elements; $i++) {
      switch ($i) {
        case '1':
          $form_element_prefix = 'st';
        break;
        case '2':
          $form_element_prefix = 'nd';
        break;
        case '3':
          $form_element_prefix = 'rd';
        break;
        default:
          $form_element_prefix = 'th';
        break;
      }

      $form['chose_form_elements']['form_type_name_' . $i] = array(
        '#type' => 'select',
        '#title' => t($i . $form_element_prefix. ' Form Element'),
        '#required' => 'true',
        '#access' => TRUE,
        '#options' => array_map('ucfirst', $form_element_type_name),
        '#attributes' => array(
          'class' => array('form-type-name-list'),
        ),
      );
    }

  }

  $form['button'] = array(
    '#type' => 'button',
    '#access' => TRUE,
    '#value' => t('Submit'),
    '#attributes' => array(
      'class' => array('generate-form'),
    ),
  );

  if (isset($form_state['values']['chose_form_elements']) && isset($form_state['triggering_element']['#type'])) {
    if ($form_state['triggering_element']['#type'] == 'button') {
      $chose_form_elements = $form_state['values']['chose_form_elements'];
      // $form_element_type_list = variable_get('form_element_type_name', array());
      foreach ($chose_form_elements as $key => $form_element_type) {
        $show_field = show_form_field($form_element_type);
        create_checkbox_form($form, $form_state, $form_element_type, $show_field);
      }
    }
  }

  $form['submit'] = array(
  	'#type' => 'submit',
  	'#access' => TRUE,
  	'#value' => t('Generate Code'),
  	'#attributes' => array(
		  'class' => array('generate-custom-code'),
  	),
  );

  return $form;
}

function show_form_elements($form, &$form_state) {
  return $form['chose_form_elements'];
}

function validate_form_function_name($element, &$form_state) {
  $form_function_name = $form_state['values']['form_name'];
  // @TODO Check function name should not start with number and have no space.
  // if (preg_match("a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff", $validate_form_function_namename)) {

  // }
  if (function_exists($form_function_name)) {
    form_set_error('form_name', $form_function_name . ' Function already exist, Please change function name');
  }
}


function create_checkbox_form(&$form, &$form_state, $form_element_type, $show_field) {

  for ($i = 1; $i <=10; $i++) {
    $fieldset_element_name = $form_element_type . '_element_fieldset_' . $i;
    if (isset($form[$fieldset_element_name])) {
      continue;
    }

    $form[$fieldset_element_name] = array(
      '#type' => 'fieldset',
      '#title' => t(ucfirst(str_replace("_", " ", $form_element_type))),
      '#collapsible' => TRUE,
      '#access' => TRUE,
    );

    $form[$fieldset_element_name]['attributes'] = array(
      '#type' => 'fieldset',
      '#title' => t(ucfirst('attributes')),
      '#collapsible' => TRUE,
      '#collapsed'   => TRUE,
      '#weight' => 999,
    );

    break;
  }

  $form[$fieldset_element_name][$form_element_type . '_element_name'] = form_element_name_field();

  if (in_array('title', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_title'] = form_title_field();
  }
  if (in_array('access', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_access']      = form_access_field();
  }
  if (in_array('required', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_required']    = form_required_field();
  }
  if (in_array('disabled', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_disabled']    = form_disable_field();
  }
  if (in_array('default_value', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_default_value'] = form_default_value_field();
  }
  if (in_array('value', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_value'] = form_value_field();
  }
  if (in_array('title_display', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_title_display'] = form_title_display_field($form_element_type);
  }
  if (in_array('ajax', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_ajax']          = form_element_ajax_field();
    $form[$fieldset_element_name][$form_element_type . '_element_ajax_callback'] = form_element_ajax_callback_field();
    $form[$fieldset_element_name][$form_element_type . '_element_ajax_wrapper']  = form_element_ajax_wrapper_field();
    $form[$fieldset_element_name][$form_element_type . '_element_ajax_method']   = form_element_ajax_method_field();
  }
  if (in_array('resizable', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_resizable'] = form_element_resizable_field();
  }
  if (in_array('collapsed', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_collapsed'] = form_element_fieldset_collapsed_field($form_element_type);
  }
  if (in_array('collapsible', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_collapsible'] = form_element_fieldset_collapsible_field($form_element_type);
  }
  if (in_array('multiple', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_multiple'] = form_multiple_field();
  }
  if (in_array('size', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_size'] = form_size_value_field();
  }
  if (in_array('rows', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_rows'] = form_rows_value_field();
  }
  if (in_array('maxlength', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_maxlength'] = form_element_maxlength_field();
  }
  if (in_array('weight', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_weight'] = form_weight_field();
  }
  if (in_array('description', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_description'] = form_description_field();
  }
  if (in_array('element_validate', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_validate'] = form_element_validate_field();
  }
  if (in_array('allowed_value', $show_field)) {
    $form[$fieldset_element_name][$form_element_type . '_element_allowed_value'] = form_allowed_value_field();
  }
  if (in_array('attributes', $show_field)) {
    $form[$fieldset_element_name]['attributes'][$form_element_type . '_element_attributes_class'] = form_attributes_class_field();
    $form[$fieldset_element_name]['attributes'][$form_element_type . '_element_attributes_id'] = form_attributes_id_field();
    $form[$fieldset_element_name]['attributes'][$form_element_type . '_element_attributes_placeholder'] = form_attributes_placeholder_field();
  }

}

function get_form_name_and_field_submit($form, &$form_state) {
	$form_function_name = $form_state['values']['form_name'];
  $param = array('$form', '&$form_state');
  $custom_form_code  = '';
  $comment_message   = 'Form Construction.';
  $custom_form_code .= function_start_comment($comment_message);
	$custom_form_code .= function_name($form_function_name, $param);
  $custom_form_code .= generate_form_code($form, $form_state);
	$custom_form_code .= function_closing_braces();
  dpm($custom_form_code);
}

function element_validate_function_code($element_validate_function_name) {
  $param = array('$element', '&$form_state');
  $function_frame  = function_name($element_validate_function_name, $param);
  $function_frame .= function_closing_braces();
  return $function_frame;
}

function generate_form_code($form, $form_state) {
  $custom_code = "";
  $chose_form_elements = $form_state['values']['chose_form_elements'];
  $form_element_type_name = variable_get('form_element_type_name', array());
  foreach ($chose_form_elements as $key => $value) {
    $fieldset_name = $form_element_type_name[$value] . "_element_fieldset";
    $form_type_name = str_replace("_element_fieldset", "", $fieldset_name);
    for ($i = 1; $i <= 10; $i++) {
      $fieldset_element_name = $fieldset_name . '_' . $i;
      if (isset($form_state['values'][$fieldset_element_name]) && isset($form_state['values'][$fieldset_element_name]['attributes'])) {
        $field_info     = $form_state['values'][$fieldset_element_name];
        $form_base_name = str_replace("_fieldset", "", $fieldset_name);
        $custom_code   .= code_maker($field_info, $form_base_name, $form_type_name);
        unset($form_state['values'][$fieldset_element_name]);
      }
    }
  }
  return $custom_code;
}

function code_maker($field_info, $form_base_name, $form_type_name) {
  $custom_code  = "";
  $custom_code .= check_variable($field_info, $form_base_name . '_name') ? field_frame_start_code($field_info[$form_base_name . '_name']) : "";
  $custom_code .= field_type_code($form_type_name);
  $custom_code .= check_variable($field_info, $form_base_name . '_title') ? field_title_code($field_info[$form_base_name . '_title']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_access') ? field_access_code($field_info[$form_base_name . '_access']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_required') ? field_required_code($field_info[$form_base_name . '_required']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_disabled') ? field_disabled_code($field_info[$form_base_name . '_disabled']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_default_value') ? field_default_value_code($field_info[$form_base_name . '_default_value']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_value') ? field_value_code($field_info[$form_base_name . '_value']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_title_display') ? field_title_display_code($field_info[$form_base_name . '_title_display']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_resizable') ? field_resizable_code($field_info[$form_base_name . '_resizable']) : "";

  if (check_variable($field_info, $form_base_name . '_ajax')) {
    $ajax_callback = $field_info[$form_base_name . '_ajax_callback'];
    $ajax_wrapper  = check_plain($field_info[$form_base_name . '_ajax_wrapper']);
    $ajax_method   = $field_info[$form_base_name . '_ajax_method'];
    $custom_code  .= field_ajax_code($ajax_callback, $ajax_wrapper, $ajax_method);
  }

  if (check_variable($field_info, 'attributes')) {
    $class = !empty($field_info['attributes'][$form_base_name . '_attributes_class']) ? $field_info['attributes'][$form_base_name . '_attributes_class'] : NULL;
    $id    = !empty($field_info['attributes'][$form_base_name . '_attributes_id']) ? $field_info['attributes'][$form_base_name . '_attributes_id'] : NULL;
    $placeholder = !empty($field_info['attributes'][$form_base_name . '_attributes_placeholder']) ? $field_info['attributes'][$form_base_name . '_attributes_placeholder'] : NULL;
    if (isset($class) || isset($id) || isset($placeholder)) {
      $custom_code  .= field_attributes_code($class, $id, $placeholder);
    }
  }

  $custom_code .= check_variable($field_info, $form_base_name . '_collapsed') ? field_fieldset_collapsed_code($field_info[$form_base_name . '_collapsed']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_collapsible') ? field_fieldset_collapsible_code($field_info[$form_base_name . '_collapsible']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_multiple') ? field_multiple_code($field_info[$form_base_name . '_multiple']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_size') ? field_size_value_code($field_info[$form_base_name . '_size']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_rows') ? field_rows_value_code($field_info[$form_base_name . '_rows']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_weight') ? field_weight_code($field_info[$form_base_name . '_weight']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_maxlength') ? field_maxlength_code($field_info[$form_base_name . '_maxlength']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_allowed_value') ? field_allowed_value_code($field_info[$form_base_name . '_allowed_value']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_description') ? field_description_code($field_info[$form_base_name . '_description']) : "";
  $custom_code .= check_variable($field_info, $form_base_name . '_validate') ? field_element_validate_code($field_info[$form_base_name . '_validate']) : "";
  $custom_code .= field_frame_end_code();
  return $custom_code;
}

function check_variable($array_variable, $variable) {

  $variable_exit = (isset($array_variable[$variable]) && !empty($array_variable[$variable])) ? TRUE : FALSE;
  return $variable_exit;
}

function get_form_name_and_field_validate($form, &$form_state) {

  $form_element_type_name = variable_get('form_element_type_name', array());
  foreach ($form_element_type_name as $key => $value) {
    $fieldset_name = $key . "_element_fieldset";
    $form_type_name = str_replace("_element_fieldset", "", $fieldset_name);
    for ($i = 1; $i <= 10; $i++) {
      $fieldset_element_name = $fieldset_name . '_' . $i;
      if (isset($form_state['values'][$fieldset_element_name][$form_type_name . '_element_ajax'])) {
        if ($form_state['values'][$fieldset_element_name][$form_type_name . '_element_ajax'] == 1) {
          // @TODO apply element in form_set_form.
          if (empty($form_state['values'][$fieldset_element_name][$form_type_name . '_element_ajax_callback'])) {
            form_set_error('', "$key ajax Callback can't be empty");
          }
          if (empty($form_state['values'][$fieldset_element_name][$form_type_name . '_element_ajax_wrapper'])) {
            form_set_error('', "$key ajax wrapper can't be empty");
          }
        }
      }
    }
  }

}

function show_form_field($field_type) {

  $field_name = array(
    'title'            => 'title',
    'size'             => 'size',
    'rows'             => 'rows',
    'ajax'             => 'ajax',
    'value'            => 'value',
    'weight'           => 'weight',
    'access'           => 'access',
    'disabled'         => 'disabled',
    'required'         => 'required',
    'resizable'        => 'resizable',
    'maxlength'        => 'maxlength',
    'multiple'         => 'multiple',
    'collapsed'        => 'collapsed',
    'collapsible'      => 'collapsible',
    'description'      => 'description',
    'title_display'    => 'title_display',
    'allowed_value'    => 'allowed_value',
    'default_value'    => 'default_value',
    'element_validate' => 'element_validate',
    'attributes'       => 'attributes',
  );

  switch ($field_type) {
    case 'checkbox':
      $show_field = array(
        $field_name['size'],
        $field_name['rows'],
        $field_name['ajax'],
        $field_name['value'],
        $field_name['title'],
        $field_name['weight'],
        $field_name['access'],
        $field_name['disabled'],
        $field_name['required'],
        $field_name['multiple'],
        $field_name['maxlength'],
        $field_name['resizable'],
        $field_name['collapsed'],
        $field_name['attributes'],
        $field_name['collapsible'],
        $field_name['description'],
        $field_name['default_value'],
        $field_name['title_display'],
        $field_name['element_validate'],
      );
      break;

    case 'select':
      $show_field = array(
        $field_name['title'],
        $field_name['access'],
        $field_name['disabled'],
        $field_name['required'],
        $field_name['description'],
        $field_name['element_validate'],
        $field_name['allowed_value'],
      );
      break;

    case 'textfield':
      $show_field = array(
        $field_name['title'],
        $field_name['access'],
        $field_name['disabled'],
        $field_name['required'],
        $field_name['description'],
        $field_name['element_validate'],
      );
      break;

    default:
      $show_field = $field_name;
      break;
  }

  return $show_field;
}
