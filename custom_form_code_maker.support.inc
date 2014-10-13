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

function field_attributes_code($class, $id, $placeholder) {

  $attributes = "array(";
  if (isset($class)) {
    $attributes .= "'class' => array(\"$class\"), ";
  }
  if (isset($id)) {
    $attributes .= "'id' => \"$id\", ";
  }
  if (isset($placeholder)) {
    $attributes .= "'placeholder' => t(\"$placeholder\"), ";
  }
  $attributes = rtrim($attributes, ', ');
  $attributes .= ")";

  return "'#attributes' => $attributes,\n";
}

/* Print code for form element ajax */
function field_ajax_code($ajax_callback, $ajax_wrapper, $ajax_method) {

  return "#ajax => array(
         'callback' => '$ajax_callback',
         'wrapper' => '$ajax_wrapper',
         'method' => '$ajax_method',
         )\n";
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

/* Print code for form element maxlength */
function field_maxlength_code($value) {

  return "'#maxlength' => $value,\n";
}

/* Print code for form element multiple */
function field_multiple_code($boolean) {

  $boolean = set_boolean_value($boolean);
  return "'#multiple' => $boolean,\n";
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

/* Print code for form element description */
function field_description_code($description) {

  return "'#description' => t('$description'),\n";
}

/* Print code for form element markup */
function field_markup_code($html_string) {
  global $user;

  if (in_array('administrator', $user->roles)) {
    return "'#markup' => filter_xss_admin($html_string),\n";
  }

  return "'#markup' => filter_xss($html_string),\n";
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

  $options = array('before' => t('Before'), 'after' => t('After'), 'invisible' => t('Invisible'));

  if ($field_type == "radios" || $field_type == "checkboxes") {
    $options['attribute'] = t('Attribute');
  }

  $title_display_field = array(
    '#type' => 'radios',
    '#title' => t('Title Display'),
    '#options' => $options,
  );

  return $title_display_field;
}

function form_element_ajax_field() {

  $ajax_field = array(
    '#type' => 'checkbox',
    '#title' => t('Ajax'),
    '#attributes' => array('class' => array('ajax-element-field'),'checked' => 'checked'),
  );

  return $ajax_field;
}

function form_element_ajax_callback_field() {

  $ajax_callback_field = array(
    '#type' => 'textfield',
    '#title' => t('Callback'),
    '#attributes' => array('class' => array('ajax-callback-field')),
    '#element_validate' => array('validate_form_function_name'),
  );

  return $ajax_callback_field;
}

function form_element_ajax_wrapper_field() {

  $ajax_wrapper_field = array(
    '#type' => 'textfield',
    '#title' => t("Wrapper"),
    '#description' => t('Enter id of div element'),
    '#attributes' => array('class' => array('ajax-wrapper-field')),
  );

  return $ajax_wrapper_field;
}

function form_element_ajax_method_field() {

  $methods = array('replace' => 'replace', 'after' => 'after', 'append' => 'append', 'before' => 'before', 'prepend' => 'prepend');

  $ajax_method_field = array(
    '#type' => 'radios',
    '#title' => t("Ajax Method"),
    '#options' => $methods,
    '#default_value' => $methods['replace'],
    '#attributes' => array('class' => array('ajax-method-field')),
  );

  return $ajax_method_field;
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
    '#element_validate' => array('element_validate_integer_positive'),
  );

  return $weight_field;
}

function form_multiple_field() {

  $multiple_field = array(
    '#type' => 'checkbox',
    '#title' => t('Multiple'),
  );

  return $multiple_field;
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

function form_element_markup_field() {

  $element_markup_field = array(
    '#type' => 'textarea',
    '#title' => t('Markup'),
    '#description' => t('Enter valid markup string.'),
  );

  return $element_markup_field;
}

function form_element_maxlength_field() {

  $element_name_field = array(
    '#type' => 'textfield',
    '#title' => t('Maximum Length'),
    '#element_validate' => array('element_validate_integer_positive'),
  );

  return $element_name_field;
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

function form_attributes_class_field() {

  $element_attributes_field = array(
    '#type' => 'textfield',
    '#title' => t('Class'),
    '#description' => t('Enter class name with spaces.'),
  );

  return $element_attributes_field;
}

function form_attributes_id_field() {

  $element_attributes_field = array(
    '#type' => 'textfield',
    '#title' => t('ID'),
    '#element_validate' => array('no_space_string_element_validation'),
  );

  return $element_attributes_field;
}

function no_space_string_element_validation($element, &$form_state) {
  if (isset($element['#value']) && !empty($element['#value'])) {
    $form_tag_id = trim($element['#value']);
    if (no_space_string($form_tag_id)) {
      form_set_error('', t("HTML atrribute ID must not have any space."));
    }
  }
}

/**
 * check string have space or not.
 *
 * @param  String $string
 *
 * @return boolean
 */
function no_space_string($string = NULL) {
  if (isset($string) && !empty($string)) {
    if (count(explode(' ', $string)) > 1) {
      return TRUE;
    }
  }

  return FALSE;
}


function form_attributes_placeholder_field() {

  $title_field = array(
    '#type' => 'textfield',
    '#title' => t('Placeholder'),
  );

  return $title_field;
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
