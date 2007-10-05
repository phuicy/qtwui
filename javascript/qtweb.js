var QWeb = {}

QWeb.AutoUpdater = Class.create();
QWeb.AutoUpdater.prototype = Object.extend(new Object, {
    initialize: function(url) {
        new Ajax.Request(url, {method: 'get'});
    }
});

QWeb.Replacer = Class.create();
QWeb.Replacer.prototype = Object.extend(new Object, {
    initialize: function(item, url) {
        self.item = item
        self.request = new Ajax.Request(url, {
            method: 'get',
            onSuccess: function(transport) {
                    $(item).replace(transport.responseText);
            }
        });
    }
});
