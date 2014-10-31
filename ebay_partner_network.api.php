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
  $menu_object = menu_get_object();
  if (!empty($menu_object->ebay_category)) {
    $category = $menu_object->ebay_category;
  }
}
