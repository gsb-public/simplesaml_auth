<?php

/**
 * @file
 * SimpleSAML Auth module settings UI.
 */

/**
 * Provides settings pages.
 */
function simplesaml_auth_admin_settings() {

  $form['simplesaml_auth_installdir'] = array(
    '#type' => 'textfield',
    '#title' => t('SimpleSAML PHP install directory'),
    '#default_value' => variable_get('simplesaml_auth_installdir', ''),
    '#size' => 30,
    '#description' => t('The base directory of simpleSAMLphp. Absolute path with no trailing slash. Ex. /var/simplesamlphp'),
    '#element_validate' => array('token_element_validate'),
    '#after_build' => array('token_element_validate'),
    '#token_types' => array('global'),
  );

  // Display the user documentation of placeholders supported by
  // this module, as a description on the last pattern
  $form['token_help'] = array(
    '#title' => t('Replacement patterns'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['token_help']['help'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('global'),
  );


  $form['simplesaml_auth_authsource'] = array(
    '#type' => 'textfield',
    '#title' => t('Autenticaton source for this SP (default: default-sp)'),
    '#default_value' => variable_get('simplesaml_auth_authsource', 'default-sp'),
    '#description' => t('The name of the source to use from [simplesamlphp installation]/config/authsources.php'),
  );

  $form['simplesaml_auth_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Which attribute from simpleSAMLphp should be used as user\'s name'),
    '#default_value' => variable_get('simplesaml_auth_username', 'uid'),
    '#description' => t('Example: <i>uid</i> or <i>displayName</i><br />If the attribute is multivalued, the first value will be used.'),
    '#required' => TRUE,
  );


  $form['account'] = array(
    '#type' => 'fieldset',
    '#title' => t('User accounts'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['account']['simplesaml_auth_user_register'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically create Drupal accounts'),
    '#default_value' => variable_get('simplesaml_auth_user_register', 1),
    '#description' => t('Whether a Drupal account is automatically created the first time a simplesaml user logs into the site. If disabled, you will need to pre-register Drupal accounts for authorized users.'),
  );

  $form['account']['simplesaml_auth_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#field_prefix' => t('username@'),
    '#default_value' => variable_get('simplesaml_auth_domain', ''),
    '#size' => 30,
    // Hostnames can be 255 characters long.
    '#maxlength' => 255,
    '#description' => t("If provided, automatically generate each new user's e-mail address. If omitted, the e-mail field will not be populated. Other modules may be used to populate the e-mail field from CAS attributes or LDAP servers."),
  );

  $form['account']['simplesaml_auth_hide_email'] = array(
    '#type' => 'checkbox',
    '#title' => t('Users cannot change email address'),
    '#default_value' => variable_get('simplesaml_auth_hide_email', 0),
    '#description' => t('Hide email address field on the edit user form.'),
  );

  $form['account']['simplesaml_auth_hide_password'] = array(
    '#type' => 'checkbox',
    '#title' => t('Users cannot change password'),
    '#default_value' => variable_get('simplesaml_auth_hide_password', 0),
    '#description' => t('Hide password field on the edit user form. This also removes the requirement to enter your current password before changing your e-mail address.'),
  );

  $form['pages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Redirection'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['pages']['simplesaml_auth_access'] = array(
    '#type' => 'radios',
    '#title' => t('Require simplesaml login for'),
    '#default_value' => variable_get('simplesaml_auth_access', 0),
    '#options' => array(t('specific pages'), t('all pages except specific pages')),
  );

  $form['pages']['simplesaml_auth_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Specific pages'),
    '#default_value' => variable_get('simplesaml_auth_pages', ''),
    '#cols' => 40,
    '#rows' => 5,
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
  );

  $form['pages']['simplesaml_auth_exclude'] = array(
    '#type' => 'textarea',
    '#title' => t('Excluded Pages'),
    '#default_value' => variable_get('simplesaml_auth_exclude', SIMPLESAML_AUTH_EXCLUDE),
    '#cols' => 40,
    '#rows' => 5,
    '#description' => t("Indicates which pages will be ignored (no login checks). Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
  );


  $form['misc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login/Logout Destinations'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Settings for redirection upon first login
  $form['misc']['simplesaml_auth_first_login_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Initial login destination'),
    '#default_value' => variable_get('simplesaml_auth_first_login_destination', ''),
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t("Drupal path or URL. Enter a destination if you want the user to be redirected to this page on their first simplesaml login. An example path is <em>blog</em> for the blog page, <em>&lt;front&gt;</em> for the front page, or <em>user</em> for the user's page."),
  );

  // Setting for page to return to after a simplesaml logout
  $form['misc']['simplesaml_auth_logout_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Logout destination'),
    '#default_value' => variable_get('simplesaml_auth_logout_destination', ''),
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t("Drupal path or URL. Enter a destination if you want a user to be directed to this page after logging out of simplesaml, or leave blank to direct users back to the previous page. An example path is <em>blog</em> for the blog page or <em>&lt;front&gt;</em> for the front page."),
  );

  return system_settings_form($form);
}
