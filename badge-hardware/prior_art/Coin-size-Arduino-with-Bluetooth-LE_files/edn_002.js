/* AJAX Service */
function EDNService(url) {
    if (typeof _siteUrl != 'undefined') {
        this.url = _siteUrl + url;
    }
    else {
        this.url = url;
    }
}

EDNService.prototype.AjaxCall = function (options) {
    $.ajax({
        type: 'POST',
        url: this.url + options.method,
        dataType: 'json',
        data: (options.params) ? options.params : [],
        cache: false,
        success: function (data, tstatus, xhr) {
            if (options.callback) {
                options.callback(data);
            }
        }
    });
};