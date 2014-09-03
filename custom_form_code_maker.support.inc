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

/* Print code for form element default value */
function field_default_value_code($default_value) {

  return "'#default_value' => t('$default_value'),\n";
}

/* Print code for form element value */
function field_value_code($value) {

  return "'#value' => t('$value'),\n";
}

/* Print code for form element default value */
function field_title_display_code($string) {

  return "'#title_display' => '$string',\n";
}

/* Print code for form element rows */
function field_rows_value_code($row_value) {

  return "'#rows' => $row_value,\n";
}

/* Print code for form element size */
function field_size_value_code($size_value) {

  return "'#size' => $size_value,\n";
}

/* Print code for form element weight */
function field_weight_code($weight) {

  return "'#weight' => $weight,\n";
}

/* Print code for form element allowed value */
function field_allowed_value_code($string) {

  $option = list_extract_allowed_values($string, 'list_text', TRUE);
  $string = array_to_string($option);
  return "'#options' => $string,\n";
}

/* Print code for form element fieldset collapsed */
function field_fieldset_collapsed_code($boolean) {

  $boolean = set_boolean_value($boolean);
  return "'#collapsed' => $boolean,\n";
}

/* Print code for form element fieldset collapsible */
function field_fieldset_collapsible_code($boolean) {

  $boolean = set_boolean_value($boolean);
  return "'#collapsible' => $boolean,\n";
}

/* Print code for form element resizeable */
function field_resizable_code($boolean) {

  $boolean = set_boolean_value($boolean);
  return "'#resizable' => $boolean,\n";
}

function array_to_string($list, $string = '') {
  foreach ($list as $key => $value) {
    $string .= "'$key' => t('" . check_plain($value) . "'), ";
  }
  $string = rtrim($string, ', ');
  $string = "array($string)";
  return $string;
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

/**
* Form element code.
*/

function form_title_field() {

  $title_field = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
  );

  return $title_field;
}

function form_placeholder_field() {

  $title_field = array(
    '#type' => 'textfield',
    '#title' => t('Placeholder'),
  );

  return $title_field;
}

function form_required_field() {

  $required_field = array(
    '#type' => 'checkbox',
    '#title' => t('Required'),
  );

  return $required_field;
}

function form_disable_field() {

  $disable_field = array(
    '#type' => 'checkbox',
    '#title' => t('Disabled'),
  );

  return $disable_field;
}

function form_access_field() {

  $access_field = array(
    '#type' => 'checkbox',
    '#title' => t('Access'),
  );

  return $access_field;
}

function form_default_value_field() {

  $description_field = array(
    '#type' => 'textfield',
    '#title' => t('Default Value'),
  );

  return $description_field;
}

function form_value_field() {

  $value_field = array(
    '#type' => 'textfield',
    '#title' => t('Value'),
  );

  return $value_field;
}

function form_title_display_field($field_type) {

  if ($field_type == "radios" || $field_type == "checkboxes") {
    $options = array('before' => t('Before'), 'after' => t('After'), 'invisible' => t('Invisible'), 'attribute' => t('Attribute'));
  }
  else {
    $options = array('before' => t('Before'), 'after' => t('After'), 'invisible' => t('Invisible'));
  }

  $title_display_field = array(
    '#type' => 'radios',
    '#title' => t('Title Display'),
    '#options' => $options,
  );

  return $title_display_field;
}

function form_rows_value_field() {

  $rows_field = array(
    '#type' => 'textfield',
    '#title' => t('#Rows'),
    '#size' => 4,
    '#element_validate' => array('element_validate_integer_positive'),
  );

  return $rows_field;
}

function form_size_value_field() {

  $size_field = array(
    '#type' => 'textfield',
    '#title' => t('Size'),
    '#size' => 4,
    '#element_validate' => array('element_validate_integer_positive'),
  );

  return $size_field;
}

function form_weight_field() {

  $weight_field = array(
    '#type' => 'textfield',
    '#title' => t('Weight'),
    '#size' => 4,
    '#element_validate' => array('element_validate_integer_positive'),
  );

  return $weight_field;
}

function form_description_field() {

  $description_field = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
  );

  return $description_field;
}

function form_allowed_value_field() {

  $element_allowed_value_field = array(
    '#type' => 'textarea',
    '#title' => t('Allowed values list'),
    '#description' => t('The possible values this field can contain. Enter one value per line, in the format key|label.
                         The key is the stored value. The label will be used in displayed values and edit forms.
                         The label is optional: if a line contains a single string, it will be used as key and label.'),
    '#required' => TRUE,
  );

  return $element_allowed_value_field;
}

function form_element_validate_field() {

  $element_validate_field = array(
    '#type' => 'textfield',
    '#title' => t('Element Validate'),
    '#description' => t('Enter function name which have code to validate element.'),
    '#element_validate' => array('validate_form_function_name'),
  );

  return $element_validate_field;
}

function form_element_name_field() {

  $element_name_field = array(
    '#type' => 'textfield',
    '#title' => t('Element Name'),
    '#required' => TRUE,
  );

  return $element_name_field;
}

function form_element_resizable_field() {

  $element_resizable_field = array(
    '#type' => 'checkbox',
    '#title' => t('Resizable'),
  );

  return $element_resizable_field;
}


function form_element_fieldset_collapsed_field() {

  $element_fieldset_collapsed_field = array(
    '#type' => 'checkbox',
    '#title' => t('Collapsed'),
  );

  return $element_fieldset_collapsed_field;
}

function form_element_fieldset_collapsible_field() {

  $element_fieldset_collapsible_field = array(
    '#type' => 'checkbox',
    '#title' => t('Collapsible'),
  );

  return $element_fieldset_collapsible_field;
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
