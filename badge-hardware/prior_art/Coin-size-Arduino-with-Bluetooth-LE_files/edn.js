Array.prototype.shuffleBlogs = function () {
    var i = this.length, j, temp;
    if (i == 0) return;
    while (--i) {
        j = Math.floor(Math.random() * (i + 1));
        temp = this[i];
        this[i] = this[j];
        this[j] = temp;
    }
};

function EDNBlogService() {
    this.blogCollectionContainer = '<div class="blog-entry">' +
            '<div class="img"><img src="[BLOG_COLLECTION_IMAGE]" width="75px" height="75px" alt="image" class="" /></div>' +
            '<span class="red">[BLOG_COLLECTION_AUTHOR]</span>' +
            '<h3><a href="/[BLOG_COLLECTION_URL]">[BLOG_COLLECTION_TITLE]</a></h3>' +
            '<ul class="info">' +
                '<li class="follow-save"><a href="" class="Save-Follow-Link">Save & Follow</a>' +
                '<div class="save-follow-drop">' +
                    '<a href="#" itemid="Save_[BLOG_COLLECTION_ID]"  class="Save_[BLOG_COLLECTION_ID]" onclick="AddBookmark([BLOG_COLLECTION_ID], \'Save_[BLOG_COLLECTION_ID]\'); return false;" >Save to My Library</a><br/>' +
                    '<a href="#" itemid="FollowComment_[BLOG_COLLECTION_ID]"  class="FollowComment_[BLOG_COLLECTION_ID]" onclick="AddBookmark([BLOG_COLLECTION_ID], \'FollowComment_[BLOG_COLLECTION_ID]\'); return false;">Follow Comments</a><br/>' +
                    '<a href="#" style=display:[BLOG_COLLECTION_ISHIDDEN]  itemid="FollowAuthor_[BLOG_COLLECTION_AuthorId]" class="FollowAuthor_[BLOG_COLLECTION_AuthorId]_[BLOG_COLLECTION_ID]"   onclick="FollowAuthor([BLOG_COLLECTION_ID], [BLOG_COLLECTION_AuthorId], \'FollowAuthor_[BLOG_COLLECTION_AuthorId]_[BLOG_COLLECTION_ID]\'); return false;"  >Follow Author</a>' +
                '</div>   ' +
                '</li>' +
            '</ul>' +
            '<div class="blog-titles">[BLOG_COLLECTION_BLOGS]</div>' +
        '</div>';
    this.blogContainer = '<p><a href="/[BLOG_URL]">[BLOG_TITLE]</a></p>';

    this.loadBlogs = function (id, page, maxItms, rand) {
        this.AjaxCall({
            method: 'LoadBlogs',
            params: { containerId: id, page: page, maxItems: maxItms, randomize: rand },
            callback: function (data) {
                blogsLoaded(data);
                $('#blogs-container').attr('data-currentPage', page);
                _bookmarkService.setupSaveFollowLinks('.blog-entry');
            }
        });
    };

    this.shuffleBlogs = function () {
        var blogArray = $('.blog-entry').toArray();
        blogArray.shuffleBlogs();

        $('.blog-entry').remove();
        var allBlogs = '';
        $.each(blogArray, function () {
            allBlogs += '<div class="blog-entry">' + $(this).html() + '</div>';
        });

        // Update to the rest of the blog
        $('#blogs-container').prepend($(allBlogs).hide().slideDown('slow'));

        // go through all divs and adjust styles
        var i = 1;
        $('.blog-entry').removeClass('last');
        $('.blog-entry').each(function () {
            if (i % 3 == 0) {
                $(this).addClass('last');
            }
            i++;
        });
        $('#blogs-loader').html('');
    };
}
EDNBlogService.prototype = new EDNService('/Community/');
var _blogService = new EDNBlogService();



function blogsLoaded(data) {
    var allBlogs = '';
    $.each(data, function () {
        var collection = _blogService.blogCollectionContainer;
        var blogs = '';

        collection = collection.replace(/\[BLOG_COLLECTION_IMAGE\]/g, this.ContentImageUrl);
        collection = collection.replace(/\[BLOG_COLLECTION_AUTHOR\]/g, this.CollectionAuthor);
        collection = collection.replace(/\[BLOG_COLLECTION_URL\]/g, this.RelativeUrl);
        collection = collection.replace(/\[BLOG_COLLECTION_TITLE\]/g, this.Title);
        collection = collection.replace(/\[BLOG_COLLECTION_ID\]/g, this.Id);
        if (this.AuthorId != null) {
            collection = collection.replace(/\[BLOG_COLLECTION_AuthorId\]/g, this.AuthorId);
        }
        else {
            collection = collection.replace(/\[BLOG_COLLECTION_ISHIDDEN\]/g, 'none');
        }
        $.each(this.Blogs, function () {
            var blogContainer = _blogService.blogContainer;

            blogContainer = blogContainer.replace('[BLOG_TITLE]', this.Title);
            blogContainer = blogContainer.replace('[BLOG_URL]', this.RelativeUrl);

            blogs += blogContainer;
        });

        collection = collection.replace('[BLOG_COLLECTION_BLOGS]', blogs);
        allBlogs += collection;
    });

    // Update count
    var curCount = parseInt($('#blogs-current-count').html());
    var totalItems = parseInt($('#blogs-container').attr('data-totalItems'));
    curCount += data.length;
    $('#blogs-current-count').html(curCount);
    // disable load more when current items = total items
    if (curCount < totalItems) {
        $('#blogs-load-more').live('click', loadMoreBlogs);
        $('#blogs-load-more').css('opacity', '1');
    }

    $('#blogs-loader').html('');
    
    // Update to the rest of the blog
    $('#blogs-container').prepend($(allBlogs).hide().slideDown('slow'));

    // go through all divs and adjust styles
    var i = 1;
    $('.blog-entry').removeClass('last');
    $('.blog-entry').each(function () {
        if (i % 3 == 0) {
            $(this).addClass('last');
        }
        i++;
    });
}

function loadMoreBlogs(event) {
    event.preventDefault();
    $('#blogs-load-more').die('click');
    $('#blogs-load-more').css('opacity', '.5');
    var nextPage = parseInt($('#blogs-container').attr('data-currentPage')) + 1;
    var maxItems = parseInt($('#blogs-container').attr('data-maxItems'));
    $('#blogs-loader').html('Loading more blogs...'); // make gif?
    _blogService.loadBlogs($('#blogs-container').attr('data-containerId'), nextPage, maxItems, false);
}

$(document).ready(function () {
    var nextPage = parseInt($('#blogs-container').attr('data-currentPage'));
    var maxItems = parseInt($('#blogs-container').attr('data-maxItems'));
    $('#blogs-show-all').click(function () {
        _blogService.loadBlogs($('#blogs-container').attr('data-containerId'), nextPage, maxItems, false);
    });

    $('#blogs-load-more').live('click', loadMoreBlogs);
    
    $('#blogs-shuffle').live('click', function (event) {
        event.preventDefault();
        $('#blogs-loader').html('Shuffling...'); // make gif?
        _blogService.shuffleBlogs();
    });
});