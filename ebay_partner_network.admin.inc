<?php

/**
 * @file
 * Ebay Partner Network Administration pages.
 */

/**
 * Returns with the general configuration form.
 *
 * @ingroup forms
 * @see system_settings_form()
 *
 * @param array $form
 *   A Drupal form.
 * @param array $form_state
 *   The current state of the form.
 *
 * @return array
 *   Output of the system_settings_form()
 */
function ebay_partner_network_admin_settings($form, &$form_state) {
  $app_id = variable_get('ebay_partner_network_app_id','');

  $form['ebay_partner_network_app_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Ebay APP ID'),
    '#description' => t('Ebay APP ID'),
    '#default_value' => $app_id,
    '#required' => TRUE,
  );

  $form['ebay_partner_network_store_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Ebay Store Id'),
    '#description' => t('The ebay store ID'),
    '#default_value' => variable_get('ebay_partner_network_store_id', 'EBAY-GB'),
  );

  $form['ebay_partner_network_items_num'] = array(
    '#type' => 'select',
    '#title' => t('Number Of Items to be displayed'),
    '#options' => range(0,50),
    '#default_value' => variable_get('ebay_partner_network_items_num', 5),
  );

  if(!empty($app_id)) {
    $categories = ebay_partner_network_get_categories($app_id);
    $form['ebay_partner_network_default_category'] = array(
      '#type' => 'select',
      '#title' => t('Default Category'),
      '#options' => $categories,
      '#default_value' => variable_get('ebay_partner_network_default_category', ''),
    );
  }

  $form['fieldset_affiliate'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ebay Partner Network'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['fieldset_affiliate']['ebay_partner_network_campaign_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Campaign ID'),
    '#description' => t('10-digit Campaign ID'),
    '#default_value' => variable_get('ebay_partner_network_campaign_id', ''),
  );
  $form['fieldset_affiliate']['ebay_partner_network_network_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Network ID'),
    '#description' => t('Network ID'),
    '#default_value' => variable_get('ebay_partner_network_network_id', 9),
  );
  $form['fieldset_affiliate']['ebay_partner_network_custom_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom ID'),
    '#description' => t('Custom ID'),
    '#default_value' => variable_get('ebay_partner_network_custom_id', ''),
  );

  return system_settings_form($form);
}