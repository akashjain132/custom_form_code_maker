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
      $form['chose_form_elements']['form_type_name_' . $i] = array(
        '#type' => 'select',
        '#required' => 'true',
        '#access' => TRUE,
        '#options' => $form_element_type_name,
        '#attributes' => array(
          'class' => array('form-type-name-list'),
        ),
      );
    }

  }

  $form['submit'] = array(
  	'#type' => 'submit',
  	'#access' => TRUE,
  	'#value' => t('Generate Code'),
  	'#attributes' => array(
  		'class' => array('generate_custom_code'),
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
