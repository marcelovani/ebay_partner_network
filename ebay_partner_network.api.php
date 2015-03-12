<?php

/**
 * @file
 * Documents API functions for the Ebay Parner Network module.
 */

/**
 * Alter the keyword before performing the search on Ebay.
 */
function hook_ebay_partner_network_keyword_alter(&$kw) {
  $menu_object = menu_get_object();
  if (!empty($menu_object->ebay_keyword)) {
    $kw = $menu_object->ebay_keyword;
  }
}

/**
 * Alter the category before performing the search on Ebay.
 */
function hook_ebay_partner_network_category_alter(&$category) {
  // Getting all fields of the 'ebay_category' type.
  $ebay_category_fields = ebay_partner_network_category_fields();
  if (count($ebay_category_fields) > 0) {
    // Checking if ebay category is set on the primary category.
    // If yes, then use it.
    $menu_object = menu_get_object();
    if (!empty($menu_object->field_category_primary[LANGUAGE_NONE])) {
      foreach ($menu_object->field_category_primary[LANGUAGE_NONE] as $term) {
        foreach (array_keys($ebay_category_fields) as $cat) {
          if (!empty($term['taxonomy_term']->$cat)) {
            if (!empty($term['taxonomy_term']->{$cat}[LANGUAGE_NONE][0]['option'])) {
              $category = $term['taxonomy_term']->{$cat}[LANGUAGE_NONE][0]['option'];
              break;
            }
          }
        }
      }
    }
  }
}

/**
 * Adding more params to Ebay API call.
 *
 * More info about available filters:
 * http://developer.ebay.com/Devzone/finding/CallRef/findItemsAdvanced.html
 *
 * @param array $custom_params
 *   Array containing custom parameters.
 */
function hook_ebay_partner_network_custom_params_alter(&$custom_params) {
  $custom_params['itemFilter'][] = array('name' => 'Condition', 'value' => 'New');
  $custom_params['itemFilter'][] = array('name' => 'ListingType', 'value' => 'FixedPrice');
  $custom_params['itemFilter'][] = array(
    'name' => 'MinPrice', 'value' => '500.00', 'paramName' => 'Currency', 'paramValue' => 'GBP',
  );
}
