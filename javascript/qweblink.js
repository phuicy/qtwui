/**
 * Calls a handler slot on the server and optionally updates the DOM of the current page.
 * \param url url of the server Ajax handler slot.
 * \param params parameters to send to the server in an url encoded form (optional).
 * \param destination DOM element to update with the response brought back by the AJAX request (optional).
 * \param mth DOM element update method see <a href="http://www.prototypejs.org/api/insertion">Insertion</a>.
 */
function handleAjaxClick(url, params, destination, mth)
{
    var p = params;
    if (p == null) {
        p = {};
    }
    if (destination != null) {
        new Ajax.Updater(destination, url, {method: 'get', parameters: p, insertion: mth});
    } else {
        new Ajax.Request(url, {method: 'get', parameters: p});
    }
}
