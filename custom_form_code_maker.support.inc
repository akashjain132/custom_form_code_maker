<?php

/* Print code for form element name */
function field_frame_start_code($field_name) {

  return "\$form['$field_name'] = array(\n";
}

/* Print code for end form element name */
function field_frame_end_code() {

  return ");\n\n";
}

/* Print code for form type */
function field_type_code($field_type) {

  return "'#type' => '$field_type',\n";
}

/* Print code for form element title */
function field_title_code($title_name) {

  return "'#title' => t('$title_name'),\n";
}

/* Print code for form element access */
function field_access_code($boolean) {

  $boolean = set_boolean_value($boolean);
  return "'#access' => $boolean,\n";
}

/* Print code for form element required */
function field_required_code($boolean) {

  $boolean = set_boolean_value($boolean);
  return "'#required' => $boolean,\n";
}

/* Print code for form element placeholder */
function field_placeholder_code($placeholder_name) {

  return "'#placeholder' => t('$placeholder_name'),\n";
}

/* Print code for form element disable */
function field_disabled_code($boolean) {

  $boolean = set_boolean_value($boolean);
  return "'#disabled' => $boolean,\n";
}

/* Print code for form element discription */
function field_description_code($description) {

  return "'#description' => t('$description'),\n";
}

/* Print code for form element validate function */
function field_element_validate_code($element_validate_function_name) {

  return "'#element_validate' => array('$element_validate_function_name'),\n";
}

/* Print code for function comment */
function function_start_comment($comment_message) {

  return "/**\n *$comment_message\n */\n";
}

/* Print code for opening function braces */
function function_opening_braces() {

  return " {\n\n";
}

/* Print code for closing function braces */
function function_closing_braces() {

  return "\n}";
}

/* Set boolean value */
function set_boolean_value($boolean) {

  return $boolean == 1 ? 'TRUE' : 'FALSE';
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

function form_element_name_field() {

  $element_name_field = array(
    '#type' => 'textfield',
    '#title' => t('Element Name'),
    '#access' => TRUE,
    '#required' => TRUE,
  );

  return $element_name_field;
}

/* Print code for function name */
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
