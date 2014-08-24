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
        '#options' => $form_element_type_name,
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
  $form[$fieldset_element_name]['checkbox_element_access']      = form_access_field();
  $form[$fieldset_element_name]['checkbox_element_required']    = form_required_field();
  $form[$fieldset_element_name]['checkbox_element_disabled']    = form_disable_field();
  $form[$fieldset_element_name]['checkbox_element_description'] = form_description_field();
  $form[$fieldset_element_name]['checkbox_element_validate']    = form_element_validate_field();

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
    '#title' => t('Disabled'),
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
  $custom_form_code   = '';
  $custom_form_code  .= function_start_comment();
	$custom_form_code  .= function_name($form_function_name);
	$custom_form_code  .= function_closing_braces();
}

function function_start_comment() {
  $function_start_comment = "/**\n *Form constructor.\n */\n";

  return $function_start_comment;
}

function function_name($form_function_name) {
  $function_name = "function {$form_function_name}(\$form, \$form_state) {";

  return $function_name;
}

function function_closing_braces() {
  $function_closing_braces = "\n}";

  return $function_closing_braces;
}
