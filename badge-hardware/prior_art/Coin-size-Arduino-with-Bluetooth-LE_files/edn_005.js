$(document).ready(function () {
    //$('.sharebar').sharebar({ horizontal: 'true', swidth: '80', minwidth: 200, position: 'left', leftOffset: 15, rightOffset: 0 });
});

function openprintviewwindow(popupUrl) {

    var newwindow = window.open(popupUrl, 'ContentDetail', 'width=600,height=400,menubar=yes,status=no,location=no,toolbar=no,scrollbars=yes,resizable=yes');
    if (window.focus) {
        newwindow.focus();
    }
    return false;
}