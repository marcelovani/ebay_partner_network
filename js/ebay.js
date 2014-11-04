(function ($) {
  Drupal.behaviors.ebay_partner_network = {
    attach: function (context, settings) {
      var conf = Drupal.settings.ebay_partner_network;
      var url = "http://svcs.ebay.com/services/search/FindingService/v1";
          url += "?OPERATION-NAME=findItemsAdvanced";
          url += "&SERVICE-VERSION=1.12.0";
          url += "&SECURITY-APPNAME="+conf.app_id;
          url += "&GLOBAL-ID="+conf.store_id;
          url += "&RESPONSE-DATA-FORMAT=JSON";
          url += "&callback=_cb_findItemsAdvanced";
          url += "&REST-PAYLOAD";
          url += "&categoryId="+conf.category;
          url += "&keywords="+conf.keyword;
          url += "&paginationInput.entriesPerPage="+conf.items_num;
          if(conf.campaign_id) {
            url += "&affiliate.trackingId="+conf.campaign_id;
            if(conf.network_id) {
              url += "&affiliate.networkId="+conf.network_id;
            }
            if(conf.custom_id) {
              url += "&affiliate.customId="+conf.custom_id;
            }
          }
          if(conf.custom_params){
           url += conf.custom_params;
          }

       s = document.createElement('script');
       s.src = url;
       document.body.appendChild(s);
    }
  };
})(jQuery);


function _cb_findItemsAdvanced(root) {
   var items = root.findItemsAdvancedResponse[0].searchResult[0].item || [];
   if(items.length > 0) {
     var html = Drupal.theme('ebayItemsTheme', items);
     document.getElementById("ebay_items").innerHTML = html.join("");
     document.getElementById("block-ebay-partner-network-pn-related-ebay-items").style.display = "block";
   }
   else {
     document.getElementById("block-ebay-partner-network-pn-related-ebay-items").style.display = "none";
   }
}

Drupal.theme.prototype.ebayItemsTheme = function(items) {
  var html = [];
  html.push('<table width="100%" border="0" cellspacing="0" cellpadding="4"><tbody>');
  for (var i = 0; i < items.length; ++i) {
    if (null != items[i].title && null != items[i].viewItemURL) {
      html.push('<tr><td>' + '<img src="' + items[i].galleryURL + '" border="0">' + '</td>');
      html.push('<td><a href="' + items[i].viewItemURL + '" target="_blank">' + items[i].title + '</a></td><td>'+parseFloat(items[i].sellingStatus[0].currentPrice[0].__value__).toFixed(2)+' '+items[i].sellingStatus[0].currentPrice[0]['@currencyId']+'</td>');
      html.push('</tr>');
    }
  }
  html.push('</tbody></table>');
  return html;
}