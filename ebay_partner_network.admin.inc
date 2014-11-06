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

  $ids = ebay_partner_network_site_ids();
  $ids = array_keys($ids);
  $ebay_site_names = array_combine($ids, $ids);

  $form['ebay_partner_network_store_id'] = array(
    '#type' => 'select',
    '#title' => t('Ebay Store Id'),
    '#options' => $ebay_site_names,
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
    $form['fieldset_category'] = array(
      '#type' => 'fieldset',
      '#title' => t('Ebay Category Settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $categories = ebay_partner_network_get_categories($app_id);
    $form['fieldset_category']['ebay_partner_network_default_category'] = array(
      '#type' => 'select',
      '#title' => t('Default Category'),
      '#options' => $categories,
      '#default_value' => variable_get('ebay_partner_network_default_category', ''),
    );
    $form['fieldset_category']['ebay_partner_network_category_depth'] = array(
      '#type' => 'select',
      '#title' => t('Category Depth'),
      '#options' => range(1,6),
      '#default_value' => variable_get('ebay_partner_network_category_depth', 1),
    );
    $form['fieldset_category']['ebay_partner_network_category_ids'] = array(
      '#type' => 'textfield',
      '#title' => t('Categories which children will be loaded to the depth specified in "Category Depth" setting'),
      '#description' => t('Comma separated list of IDs. E.g. 20081,625 will load all child categories of Antiques and Cameras & Photography to the depth specified in "Category Depth"'),
      '#default_value' => variable_get('ebay_partner_network_category_ids', ''),
    );
    $form['fieldset_category']['ebay_partner_network_regenerate_category_tree'] = array(
      '#type' => 'checkbox',
      '#title' => t('Tick if you want to regenerate category tree (might take some time)'),
      '#default_value' => FALSE,
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
  
  $form = system_settings_form($form);
  // Add our own submit callback last in the queue.
  $form['#submit'][] = 'ebay_partner_network_admin_form_submit';
  
  return $form;
}

/**
 * Custom 'ebay_partner_network_admin_settings' form submit callback.
 */
function ebay_partner_network_admin_form_submit($form, &$form_state) {
  if($form_state['values']['ebay_partner_network_regenerate_category_tree']) {
    ebay_partner_network_regenerate_ebay_category_tree();
  }
}
