<?php

/**
 * @file
 * Have some functions used in custom form code maker.
 */

function custom_form_code_maker() {

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

  if (isset($form_state['values']['chose_form_elements'])) {
    $chose_form_elements = $form_state['values']['chose_form_elements'];
    // $form_element_type_list = variable_get('form_element_type_name', array());
    foreach ($chose_form_elements as $key => $form_element_type) {
      switch ($form_element_type) {
        case 4:
          create_checkbox_form($form, $form_state);
          break;
        case 10:
          create_select_form($form, $form_state);
          break;
        default:
          break;
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
  // if (preg_match("a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff", $form_function_name)) {

  // }
  if (function_exists($form_function_name)) {
    form_set_error('form_name', $form_function_name . ' Function already exist, Please change function name');
  }
}


function create_checkbox_form(&$form, &$form_state) {

  for ($i = 1; $i <=10; $i++) {
    $fieldset_element_name = 'checkbox_element_fieldset_' . $i;
    if (isset($form[$fieldset_element_name])) {
      continue;
    }
    $form[$fieldset_element_name] = array(
      '#type' => 'fieldset',
      '#title' => t('Checkbox'),
      '#access' => TRUE,
    );
    break;
  }

  $form[$fieldset_element_name]['checkbox_element_name']        = form_element_name_field();
  $form[$fieldset_element_name]['checkbox_element_title']       = form_title_field();
  $form[$fieldset_element_name]['checkbox_element_placeholder'] = form_placeholder_field();
  $form[$fieldset_element_name]['checkbox_element_access']      = form_access_field();
  $form[$fieldset_element_name]['checkbox_element_required']    = form_required_field();
  $form[$fieldset_element_name]['checkbox_element_disabled']    = form_disable_field();
  $form[$fieldset_element_name]['checkbox_element_description'] = form_description_field();
  $form[$fieldset_element_name]['checkbox_element_validate']    = form_element_validate_field();

}

function create_select_form(&$form, $form_state) {
  for ($i = 1; $i <=10; $i++) {
    $fieldset_element_name = 'select_element_fieldset_' . $i;
    if (isset($form[$fieldset_element_name])) {
      continue;
    }
    $form[$fieldset_element_name] = array(
      '#type' => 'fieldset',
      '#title' => t('Select'),
      '#access' => TRUE,
    );
    break;
  }

  $form[$fieldset_element_name]['select_element_name']        = form_element_name_field();
  $form[$fieldset_element_name]['select_element_title']       = form_title_field();
  $form[$fieldset_element_name]['select_element_placeholder'] = form_placeholder_field();
  $form[$fieldset_element_name]['select_element_access']      = form_access_field();
  $form[$fieldset_element_name]['select_element_required']    = form_required_field();
  $form[$fieldset_element_name]['select_element_disabled']    = form_disable_field();
  $form[$fieldset_element_name]['select_element_option']      = form_option_field();
  $form[$fieldset_element_name]['select_element_description'] = form_description_field();
  $form[$fieldset_element_name]['select_element_validate']    = form_element_validate_field();

}

function form_required_field() {

  $required_field = array(
    '#type' => 'checkbox',
    '#title' => t('Required'),
    '#access' => TRUE,
  );

  return $required_field;
}

function form_disable_field() {

  $disable_field = array(
    '#type' => 'checkbox',
    '#title' => t('Disabled'),
    '#access' => TRUE,
  );

  return $disable_field;
}

function form_access_field() {

  $access_field = array(
    '#type' => 'checkbox',
    '#title' => t('Access'),
    '#access' => TRUE,
  );

  return $access_field;
}

function form_description_field() {

  $description_field = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#access' => TRUE,
  );

  return $description_field;
}

function form_option_field() {

  $option_field = array(
    '#type' => 'textarea',
    '#title' => t('Allowed values list'),
    '#description' => t('The possible values this field can contain. Enter one value per line, in the format key|label.<br/>
      The key is the stored value. The label will be used in displayed values and edit forms.<br/>
      The label is optional: if a line contains a single string, it will be used as key and label.'),
    '#access' => TRUE,
  );

  return $option_field;
}

function form_element_validate_field() {

  $element_validate_field = array(
    '#type' => 'textfield',
    '#title' => t('Element Validate'),
    '#description' => t('Enter function name which have code to validate element.'),
    '#access' => TRUE,
    '#element_validate' => array('validate_form_function_name'),
  );

  return $element_validate_field;
}

function form_title_field() {

  $title_field = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#access' => TRUE,
  );

  return $title_field;
}

function form_placeholder_field() {

  $title_field = array(
    '#type' => 'textfield',
    '#title' => t('Placeholder'),
    '#access' => TRUE,
  );

  return $title_field;
}

function form_element_name_field() {

  $element_name_field = array(
    '#type' => 'textfield',
    '#title' => t('Element Name'),
    '#access' => TRUE,
    '#required' => TRUE,
  );

  return $element_name_field;
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

function function_start_comment($comment_message) {
  $function_start_comment = "/**\n *$comment_message\n */\n";

  return $function_start_comment;
}

function function_name($form_function_name, $param = array()) {
  $function_name = "function {$form_function_name} (";
  foreach ($param as $key => $value) {
    $function_name .= $value . ', '; 
  }
  $function_name  = rtrim($function_name, ", ");
  $function_name .= ')';
  $function_name .= function_opening_braces();

  return $function_name;
}

function function_opening_braces() {
  $function_opening_braces = " {\n\n";

  return $function_opening_braces;
}

function function_closing_braces() {
  $function_closing_braces = "\n}";

  return $function_closing_braces;
}

function field_frame_start_code($field_name) {

  return "\$form['$field_name'] = array(\n";
}

function field_frame_end_code() {

  return ");\n\n";
}

function field_type_code($field_type) {

  return "'#type' => '$field_type',\n";
}

function field_title_code($title_name) {

  return "'#title' => t('$title_name'),\n";
}

function field_access_code($boolean) {

  $boolean = set_boolean_value($boolean);
  return "'#access' => $boolean,\n";
}

function field_required_code($boolean) {

  $boolean = set_boolean_value($boolean);
  return "'#required' => $boolean,\n";
}

function field_placeholder_code($placeholder_name) {

  return "'#placeholder' => t('$placeholder_name'),\n";
}

function field_disabled_code($boolean) {

  $boolean = set_boolean_value($boolean);
  return "'#disabled' => $boolean,\n";
}

function field_description_code($description) {

  return "'#description' => t('$description'),\n";
}

function field_element_validate_code($element_validate_function_name) {

  return "'#element_validate' => array('$element_validate_function_name'),\n";
}

function set_boolean_value($boolean) {
  $boolean = $boolean == 1 ? 'TRUE' : 'FALSE';
  return $boolean;
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
      if (isset($form_state['values'][$fieldset_element_name])) {
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
  $custom_code .= (check_variable($field_info[$form_base_name . '_name'])) ? field_frame_start_code($field_info[$form_base_name . '_name']) : "";
  $custom_code .= field_type_code($form_type_name);
  $custom_code .= check_variable(($field_info[$form_base_name . '_title'])) ? field_title_code($field_info[$form_base_name . '_title']) : "";
  $custom_code .= check_variable(($field_info[$form_base_name . '_placeholder'])) ? field_placeholder_code($field_info[$form_base_name . '_placeholder']) : "";
  $custom_code .= check_variable(($field_info[$form_base_name . '_access'])) ? field_access_code($field_info[$form_base_name . '_access']) : "";
  $custom_code .= (check_variable($field_info[$form_base_name . '_required'])) ? field_required_code($field_info[$form_base_name . '_required']) : "";
  $custom_code .= (check_variable($field_info[$form_base_name . '_disabled'])) ? field_disabled_code($field_info[$form_base_name . '_disabled']) : "";
  $custom_code .= (check_variable($field_info[$form_base_name . '_description'])) ? field_description_code($field_info[$form_base_name . '_description']) : "";
  $custom_code .= (check_variable($field_info[$form_base_name . '_validate'])) ? field_element_validate_code($field_info[$form_base_name . '_validate']) : "";
  $custom_code .= field_frame_end_code();
  return $custom_code;
}

function check_variable($variable) {

  $variable_exit = (isset($variable) && !empty($variable)) ? TRUE : FALSE;
  return $variable_exit;
}