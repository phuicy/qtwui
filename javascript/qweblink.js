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
