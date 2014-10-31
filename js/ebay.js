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
          url += "&categoryId="+conf.default_category;  
          url += "&keywords="+conf.kw; 
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

       s = document.createElement('script');
       s.src = url;
       document.body.appendChild(s);
    }
  };
})(jQuery);


function _cb_findItemsAdvanced(root) {
   var items = root.findItemsAdvancedResponse[0].searchResult[0].item || [];
   var html = [];
   html.push('<table width="100%" border="0" cellspacing="0" cellpadding="4"><tbody>');
    for (var i = 0; i < items.length; ++i) {
      var item = Drupal.theme('ebayItemTheme', items[i]);
      if(item) {
        html.push(item);
      }
    }
    html.push('</tbody></table>');
    document.getElementById("ebay_items").innerHTML = html.join("");
}

Drupal.theme.prototype.ebayItemTheme = function(item) {
	console.log(item.sellingStatus[0].currentPrice[0]);
  if (null != item.title && null != item.viewItemURL) {
   return '<tr><td>' + '<img src="' + item.galleryURL + '" border="0">' + '</td>' +
     '<td><a href="' + item.viewItemURL + '" target="_blank">' + item.title + '</a></td><td>'+parseFloat(item.sellingStatus[0].currentPrice[0].__value__).toFixed(2)+' '+item.sellingStatus[0].currentPrice[0]['@currencyId']+'</td>' +
     '</tr>';
  }
}