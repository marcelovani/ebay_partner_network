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
  // getting all fields of the 'ebay_category' type
  $ebay_category_fields = ebay_partner_network_category_fields();
  if(sizeof($ebay_category_fields) > 0) {
    //checking if ebay category is set on the node
    $menu_object = menu_get_object();
    foreach(array_keys($ebay_category_fields) as $cat) {
      if (!empty($menu_object->$cat)) {
        if(!empty($menu_object->{$cat}[LANGUAGE_NONE][0]['option'])) {
          //overriding category if the value was found
          $category = $menu_object->{$cat}[LANGUAGE_NONE][0]['option'];
          break;
        }
      }
    }
  }
}

/**
 * Adding more params to Ebay API call
 * @param Array $custom_params
 */
function hook_ebay_partner_network_custom_params_alter(&$custom_params) {
  $custom_params['itemFilter(0).name'] = 'Condition';
  $custom_params['itemFilter(0).value'] = 'New';
  $custom_params['itemFilter(1).name'] = 'MaxPrice';
  $custom_params['itemFilter(1).value'] = '500.00';
  $custom_params['itemFilter(1).paramName'] = 'Currency';
  $custom_params['itemFilter(1).paramValue'] = 'GBP';
  $custom_params['itemFilter(2).name'] = 'ListingType';
  $custom_params['itemFilter(2).value'] = 'FixedPrice';
}
