var _navDesignSelector    = '#nav li#Design_Center ul.SubList li a';
var _navCommunitySelector = '#nav li#Community ul.SubList li a';
var _navToolsSelector     = '#nav li#Tools_Learning ul.SubList li a';
var _navVaultSelector     = '#nav li#EDN_Vault ul.SubList li a';

function loadDesignNavigation() {
    $('#Design_Center_Flyin').load('/navigation/viewdesignnavigation', function () {
        $(_navDesignSelector).each(function () {
            $(this).mouseenter(function () {
                var container = $(this).attr('datacontainer');
                $('div.design-nav-container').hide();
                $(container).show();
                $(_navDesignSelector).removeClass("hover");
                $(this).addClass("hover");
            });
        });
    });
}

function loadToolsNavigation() {
    $('#Tools_Learning_Flyin').load('/navigation/viewtoolslearningnavigation', function () {
        $(_navToolsSelector).each(function () {
            $(this).mouseenter(function () {
                var container = $(this).attr('datacontainer');
                $('div.tools-nav-container').hide();
                $(container).show();
                $(_navToolsSelector).removeClass("hover");
                $(this).addClass("hover");
            });
        });
    });
}

function loadCommunityNavigation() {
    $('#Community_Flyin').load('/navigation/viewcommunitynavigation', function () {
        $(_navCommunitySelector).each(function () {
            $(this).mouseenter(function () {
                var container = $(this).attr('datacontainer');
                $('div.community-nav-container').hide();
                $(container).show();
                $(_navCommunitySelector).removeClass("hover");
                $(this).addClass("hover");
            });
        });
    });
}

function loadVaultNavigation() {
    $('#EDN_Vault_Flyin').load('/navigation/viewvaultnavigation', function () {
        $(_navVaultSelector).each(function () {
            $(this).mouseenter(function () {
                var container = $(this).attr('datacontainer');
                $('div.vault-nav-container').hide();
                $(container).show();
                $(_navVaultSelector).removeClass("hover");
                $(this).addClass("hover");
            });
        });
    });
}

function loadEDNMoments() {
    $('#top_promobox').load('/home/displaysitecontents div#SiteContent_EDNMoments', function (response, status, xhr) {
        if (status == 'error') {
            // TODO: Use this one after we have EDN Moments defined
            /*$('#top_promobox').html('<div style="width: 252px;height:90px;text-align: center;background-color: white;"><h3><span class="red">Error loading data</span></h3></div>');*/
            $('#top_promobox').html('<div id="SiteContent_EDNMoments" class="edn-content"><h4>EDN MOMENT</h4><a href="">FEB 3, 2012 - Here is the headline for the edn moment spot: 3 lines including date in headline</a></div><div class="edn-img"><img src="http://www.eetimes.com/Content/uploads/794909.png" width="90px" height="77px" alt="headline"/></div>');
        }
    });
}

function searchWebsite() {
    if (validateSearchText('#search_field', '#search_error')) {
        window.location = '/search?keyword=' + $('#search_field').val();
    }
}

function validateSearchText(divElement, divErr) {
    var searchtext = $.trim($(divElement).val());
    if (searchtext.indexOf("<") != -1 || searchtext.indexOf(">") != -1) {
        $(divErr).html('The search text cannot contain < or >');
        return false;
    }
    if (searchtext.toUpperCase() == 'SEARCH' || searchtext.length == 0) {
        $(divErr).html('Please enter search terms');
        return false;
    }
    return true;
}

function InitSearch() {
    //clear search field in master
    $('#search_field').focus(function () {
        $(this).val("");
    });
    $('#search_field').keypress(function (event) {
        var keycode = (event.keyCode ? event.keyCode : event.which);
        if (keycode == '13') {
            searchWebsite();
        }
        event.stopPropagation();
    });

    // top input field
    $('div.#search_submit').live('click', searchWebsite);
}

function InitUser() {
    $.ajax({
        url: '/Profile/GetCurrentUser',
        dataType: 'json',
        cache: false,
        success: function (data) {
            if (data && data.success) {
                $('#signed-in,#comment-signed-in,#login').toggle();
                $('#comment-login').hide();
                $('.welcome').html('Welcome ' + data.name);

                // toggle only if user != current user
                var curName = $('#user-public').attr('data-username');
                if (data.name != curName)
                    $('#user-public').toggle();

                if (typeof processOmniture == 'function')
                    processOmniture('Registered');
            }
            else {
                if (typeof processOmniture == 'function')
                    processOmniture('un-Registered');
            }
        },
        error: function () {
            if (typeof processOmniture == 'function')
                processOmniture('un-Registered');
        }
    });
}

function initComments() {
    // add any other initializations
    _commentService.commentContainer = '<div class="comments childcomments[LEVEL]" id="comment-[COMMENT_ID]" data-contentItemId="[CONTENTITEM_ID]">' +
        '<div class="user"><img src="[USER_IMAGE]" width="75px" height="75px" alt="" /></div>' +
        '<div class="NNA_CommentTextSubBase Level[LEVEL]"><p>[USER_SCREENNAME]</p><p>[COMMENT_TEXT]</p><p>[COMMENT_DATE]</p></div>' +
        '<div class="clear"></div>[REPLY_CONTAINER]</div>';
    _commentService.loginContainer = '<p class="reply dark_blue"><a href="[RETURN_URL]">Reply</a></p>';
    _commentService.replyContainer = '<p class="reply dark_blue"><a href="javascript:_commentService.replyToComment([CONTENTITEM_ID], [COMMENT_ID],\'[CONTENTITEM_URL]\', [LEVEL])">Reply</a></p>';
    _commentService.replyEntryContainer = '<div id="subdiv">' +
    '<p><textarea name="description" id="replyComment" cols="25" rows="4" class="postCommentTextarea" ></textarea></p>' +
    '<p><input name="submit" type="button" id="replySubmit" onclick="_commentService.postComment([CONTENTITEM_ID], $(\'#replyComment\').val(), [PARENT_COMMENT_ID], \'[CONTENTITEM_URL]\', [LEVEL])" value="Submit Comment" /> <input type="button" id="cancel" value="Cancel" onclick="_commentService.cancelSubmit()" /></p>' +
    '</div>';
    _commentService.counterText = '[COUNT] Comments';
    _commentService.initialize();
}

function initDateHelper() {
    // set up date format for the site
    _dateHelper.formatString = '[MONTH] [DAY], [YEAR] [HOUR]:[MINUTE] [AMPM] [DST]';
}

function initBookmarks() {
    _bookmarkService.saveFollowAnchor = 'a.Save-Follow-Link';
    _bookmarkService.saveFollowDropSelector = '.save-follow-drop';
    
    // setup save follow link
    _bookmarkService.setupSaveFollowLinks('');
    _bookmarkService.setupProfile();

    // set up containers n stuff here
    _bookmarkService.applySaveFollow('');
    _bookmarkService.getForUser();
}

/* 
Only put in the most used functions here 
Any global variables should start with underscore (_) 
*/
$(document).ready(function () {
    InitSearch();
    InitUser();

    //rss drop down in footer
    $(".displayRssCat img").mouseenter(function () {
        $(".rss_categories").slideToggle("slow");
    });

    // TODO: Please use the new calendar and then use jquery 1.7 'on' function
    //new universal header js
    $(".universal-header .edn").addClass("selected");
    if ($('div.universal-header div.events').length > 0) {
        //events listing in universal header
        $("div.universal-header div.events").mouseenter(function () {
            $("div.universal-header div.events").children('ul').slideDown(200);
        }).mouseleave(function () {
            $("div.universal-header div.events").children('ul').fadeOut(100);
        });
    }
    if ($('div.universal-header-for-mobile').length > 0) {
        //events listing in universal header mobile version
        $("div.universal-header-for-mobile").mouseenter(function () {
            $("div.universal-header-for-mobile").children('ul').slideDown(200);
        }).mouseleave(function () {
            $("div.universal-header-for-mobile").children('ul').fadeOut(100);
        });
    } 		

    $(".footer_image").click(function () {
        window.open('https://subscribe.ednmag.com/data/edn/welcome');
    });

    // EDN Moments
    loadEDNMoments();

    //tab-ifies all tab instances
    if ($('.tabs'))
        $(".tabs").tabs();
    
    // initialie datehelper
    initDateHelper();
    // initialize comments
    initComments();
    // initialize bookmarks
    initBookmarks();
    
    //google plus launch
    (function () {
        var po = document.createElement('script'); po.type = 'text/javascript'; po.async = true;
        po.src = 'https://apis.google.com/js/plusone.js';
        var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(po, s);
    })();

    //deplay main navigation
    var config = {
        over: makeTall, // function = onMouseOver callback (REQUIRED)    
        timeout: 250, // number = milliseconds delay before onMouseOut    
        out: makeShort, // function = onMouseOut callback (REQUIRED)    
        sensitivity: 7, // number = sensitivity threshold (must be 1 or higher)    
        interval: 100 // number = milliseconds for onMouseOver polling interval    
    };
    $('ul#nav li').hoverIntent(config);
    $("ul li.latest").click(function (e) {
        // e == our event data
        e.preventDefault();
    });

    // load lecture topper
    if ($('#main div.announcements')) {
        $('#main div.announcements').load('/home/displaysitecontents div#lecture_topper', function (response, status, xhr) {
            if (status == 'error') {
                $('#main div.announcements').html('<div id="lecture_topper_filler"></div>');
            }
        });
    }
});

// mouseover
function makeTall() {
    $(this).find('span.title').addClass('hover');
    $(this).find('div.SubList_Div').css('display', 'block');
}
// mouseout
function makeShort() {
    $(this).find('span:first-child').removeClass('hover');
    $(this).find('div.SubList_Div').css('display', 'none');
}

function registrationFormLoad() {
        $("#JobFunctionId,#IndustryId").live("change", function () {
            var otherSpan = $("span." + $(this).attr('id'));
            if ($(this).find('option[value="' + $(this).val() + '"]').text().toUpperCase() === "OTHER") {
                var label = "The Other " + $('label[for="' + $(this).attr('id') + '"]').text() + " field is required.";
                otherSpan.show();
                otherSpan.find("input").rules("add", {
                    required: true,
                    messages: { required: label }
                });
            } else {
                otherSpan.hide();
                otherSpan.find("input").rules("remove");
            }
        });

        addBlur('@Url.Action("CheckEmail","Profile")', "Email");
        addBlur('@Url.Action("CheckScreenName", "Profile")', "Name");

    }

function addBlur(url, fieldname) {
        $("#" + fieldname).live('blur', function () {
            var params = {};
            params[fieldname] = $("#" + fieldname).val();

            $.ajax({
                type: "post", datatype: "json", url: url, data: params,
                success: function (exists) {
                    if (exists) { $("span[exists=" + fieldname + "]").show(); } else { $("span[exists=" + fieldname + "]").hide(); }
                }
            });
        });
        $("#" + fieldname).trigger("blur");
    }

function Omniture_trackFileDownload(url) {
                var s=s_gi('cmpglobalvista'); 
                s.evar4= url;
                  s.events='event3';
                  s.tl(this,'o','File Download Requiring Registration');
}

