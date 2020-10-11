/**
 * Project: Minerva KB
 * Copyright: 2015-2016 @KonstruktStudio
 */
(function ($) {

    var GLOBAL_DATA = window.MinervaKB;

    var i18n = GLOBAL_DATA.i18n;
    var platform = GLOBAL_DATA.platform;
    var settings = GLOBAL_DATA.settings;
    var info = GLOBAL_DATA.info;

    /**
     * libs
     */
    if (!String.prototype.trim) {
        String.prototype.trim = function () {
            return this.replace(/^[\s\uFEFF\xA0]+|[\s\uFEFF\xA0]+$/g, '');
        };
    }

    /**
     * Debounces function execution
     * TODO: make shared utils lib
     * @param func
     * @param wait
     * @param immediate
     * @returns {Function}
     */
    function debounce(func, wait, immediate) {
        var timeout;
        return function () {
            var context = this, args = arguments;
            var later = function () {
                timeout = null;
                if (!immediate) {
                    func.apply(context, args);
                }
            };
            var callNow = immediate && !timeout;
            clearTimeout(timeout);
            timeout = setTimeout(later, wait);
            if (callNow) {
                func.apply(context, args);
            }
        };
    }

    /**
     * Throttles function execution. Based on Ben Alman implementation
     * TODO: make shared utils lib
     * @param delay
     * @param noTrailing
     * @param callback
     * @param atBegin
     * @returns {wrapper}
     */
    function throttle(delay, noTrailing, callback, atBegin) {
        var timeoutId;
        var lastExec = 0;

        if (typeof noTrailing !== 'boolean') {
            atBegin = callback;
            callback = noTrailing;
            noTrailing = undefined;
        }

        function wrapper() {
            var elapsed = +new Date() - lastExec;
            var args = arguments;

            var exec = function _exec() {
                lastExec = +new Date();
                callback.apply(this, args );
            }.bind(this);

            function clear() {
                timeoutId = undefined;
            }

            if (atBegin && !timeoutId) {
                exec();
            }

            timeoutId && clearTimeout(timeoutId);

            if (atBegin === undefined && elapsed > delay) {
                exec();
            } else if (noTrailing !== true) {
                timeoutId = setTimeout(
                    atBegin ?
                        clear :
                        exec,
                    atBegin === undefined ?
                    delay - elapsed :
                        delay
                );
            }
        }

        return wrapper;
    }

    function addAjaxNonce(data) {
        data['nonce_key'] = GLOBAL_DATA.nonce.nonceKey;
        data['nonce_value'] = GLOBAL_DATA.nonce.nonce;

        return data;
    }

    /**
     * Sends Google Analytics event, if API available
     * @param category
     * @param action
     * @param label
     * @param value
     */
    function trackGoogleAnalytics(category, action, label, value) {
        if (window.ga && typeof window.ga === 'function') {
            ga('send', 'event', category, action, label, value, {
                nonInteraction: true
            });
        }
    }

    // theme
    var ajaxUrl = GLOBAL_DATA.ajaxUrl;
    var $kbSearch = $('.kb-search__input');
    var NO_RESULTS_CLASS = 'kb-search__input-wrap--no-results';
    var HAS_CONTENT_CLASS = 'kb-search__input-wrap--has-content';
    var HAS_RESULTS_CLASS = 'kb-search__input-wrap--has-results';
    var REQUEST_CLASS = 'kb-search__input-wrap--request';
    var hasResults = false;
    var resultsCount = 0;
    var activeResult = -1;
    var ESC = 27;
    var ARROW_LEFT = 37;
    var ARROW_UP = 38;
    var ARROW_RIGHT = 39;
    var ARROW_DOWN = 40;
    var $doc = $('html, body');
    var $adminBar = $('#wpadminbar');
    var adminOffset = $adminBar.length ? $adminBar.height() : 0;

    /**
     * Live search result handler
     * @param $search
     * @param response
     */
    function handleSearchResultsReceive($search, response) {
        var $wrap = $search.parents('.kb-search__input-wrap');
        var $summary = $wrap.find('.kb-search__results-summary');
        var $results = $wrap.find('.kb-search__results');
        var results = response.result;
        var searchNeedle = response.search;
        var resultsContent;
        var searchShowTopics = $search.data('show-results-topic') === 1;
        var showTopicsLabel = $search.data('topic-label');

        if (results && results.length) {
            if (settings['track_search_with_results']) {
                trackGoogleAnalytics(
                    settings['ga_good_search_category'],
                    settings['ga_good_search_action'],
                    searchNeedle,
                    settings['ga_good_search_value'] || 0
                );
            }

            hasResults = true;
            resultsCount = results.length;
            activeResult = -1;
            $wrap.removeClass(NO_RESULTS_CLASS).addClass(HAS_RESULTS_CLASS);
            $summary.html(results.length + ' ' + (results.length === 1 ? i18n['result'] : i18n['results']));
            resultsContent = results.reduce(function ($el, result) {
                return $el.append(
                    '<li>' +
                        '<a href="' + result.link + '">' +
                            '<span class="kb-search__result-title">' +
                            result.title +
                            '</span>' +
                            (searchShowTopics ?
                                '<span class="kb-search__result-topic">' +
                                    '<span class="kb-search__result-topic-label">' + showTopicsLabel + '</span>' +
                                    result.topics[0] +
                                '</span>' :
                                '') +
                        '</a>' +
                    '</li>'
                );
            }, $('<ul></ul>'));
            $results.html(resultsContent);
        } else {
            if (settings['track_search_without_results']) {
                trackGoogleAnalytics(
                    settings['ga_bad_search_category'],
                    settings['ga_bad_search_action'],
                    searchNeedle,
                    settings['ga_bad_search_value'] || 0
                );
            }

            hasResults = false;
            resultsCount = 0;
            activeResult = -1;
            $wrap.removeClass(HAS_RESULTS_CLASS).addClass(NO_RESULTS_CLASS);
            $summary.html(i18n['no-results']);
            $results.html('');
        }
    }

    function focusInput() {
        $kbSearch.filter('[data-autofocus="1"]').focus();
    }

    function nextSearchResult() {
        var $resultItems = $('.kb-search__results li a');

        activeResult = activeResult + 1 >= resultsCount ? 0 : activeResult + 1;
        $resultItems.eq(activeResult).focus();
    }

    function prevSearchResult() {
        var $resultItems = $('.kb-search__results li a');

        activeResult = activeResult - 1 < 0 ? resultsCount - 1 : activeResult - 1;
        $resultItems.eq(activeResult).focus();
    }

    /**
     * Live search keypress handler
     * @param e
     */
    function onSearchKeyPress(e) {

        if (!$(".kb-search__input").is(":focus") && !$(".kb-search__results a").is(":focus")) {
            return; //we do not to mess with keypress unless search is in focus
        }

        switch (e.keyCode) {
            case ESC:
                focusInput();
                break;

            case ARROW_UP:
                prevSearchResult();
                break;

            case ARROW_DOWN:
                nextSearchResult();
                break;

            default:
                return;
        }

        e.preventDefault(); // prevent the default action (scroll / move caret)
    }

    /**
     * Lice search type handler
     * @param $search
     */
    function onSearchType($search) {
        var $wrap = $search.parents('.kb-search__input-wrap');
        var needle = $search.val() && $search.val().trim();
        var topics = $search.data('topic-ids');

        if (needle) {
            $wrap.addClass(HAS_CONTENT_CLASS);
        } else {
            $wrap.removeClass(HAS_CONTENT_CLASS);
        }

        if (!needle || needle.length < 3) {
            hasResults = false;
            resultsCount = 0;
            activeResult = -1;
            $wrap.removeClass(HAS_RESULTS_CLASS).removeClass(NO_RESULTS_CLASS);
            return;
        }

        $search.attr('disabled', 'disabled');
        $wrap.addClass(REQUEST_CLASS);

        jQuery.ajax({
            method: 'POST',
            url: ajaxUrl,
            dataType: 'json',
            data: addAjaxNonce({
                action: 'mkb_kb_search',
                search: needle,
                topics: topics
            })
        })
            .then(handleSearchResultsReceive.bind(this, $search))
            .always(function () {
                $search
                    .attr('disabled', false)
                    .focus();

                $wrap.removeClass(REQUEST_CLASS);
            });
    }

    /**
     * Article pageview tracking
     */
    function trackArticleView() {
        var $tracking_meta = $('.mkb-article-extra__tracking-data');

        if (!$tracking_meta.length) {
            return;
        }

        var $id = $tracking_meta.data('article-id');

        if (!$id) {
            return;
        }

        jQuery.ajax({
            method: 'POST',
            url: ajaxUrl,
            dataType: 'json',
            data: addAjaxNonce({
                action: 'mkb_article_pageview',
                id: $id
            })
        });
    }

    /**
     * Article like
     * @param e
     */
    function handleArticleLike(e) {
        e.preventDefault();

        var $likeBtn = $(e.currentTarget);
        var id = $likeBtn.data('article-id');
        var title = $likeBtn.data('article-title');
        var $count = $('.mkb-article-extra__stats-likes');
        var likes = parseInt($count.text(), 10);

        if (!id || $likeBtn.hasClass('mkb-voted') || $likeBtn.hasClass('mkb-disabled')) {
            return;
        }

        $likeBtn.addClass('mkb-voted');
        $('.mkb-article-extra__dislike').addClass('mkb-disabled');
        $count.text(++likes);

        jQuery.ajax({
            method: 'POST',
            url: ajaxUrl,
            dataType: 'json',
            data: addAjaxNonce({
                action: 'mkb_article_like',
                id: id
            })
        }).done(function() {
            if (settings['track_article_likes']) {
                trackGoogleAnalytics(
                    settings['ga_like_category'],
                    settings['ga_like_action'],
                    settings['ga_like_label'] === 'article_title' ? title : id,
                    settings['ga_like_value'] || 0
                );
            }

            if (settings['show_like_message']) {
                $('.fn-rating-likes-block')
                    .html($('<div class="mkb-article-extra__message">' + i18n['like_message_text'] + '</div>'));
            }

            if (settings['enable_feedback'] &&
                (settings['feedback_mode'] === 'like' || settings['feedback_mode'] === 'any')) {
                addFeedbackForm();
            }
        });
    }

    /**
     * Article dislike
     * @param e
     */
    function handleArticleDislike(e) {
        e.preventDefault();

        var $dislikeBtn = $(e.currentTarget);
        var id = $dislikeBtn.data('article-id');
        var title = $dislikeBtn.data('article-title');
        var $count = $('.mkb-article-extra__stats-dislikes');
        var dislikes = parseInt($count.text(), 10);

        if (!id || $dislikeBtn.hasClass('mkb-voted') || $dislikeBtn.hasClass('mkb-disabled')) {
            return;
        }

        $dislikeBtn.addClass('mkb-voted');
        $('.mkb-article-extra__like').addClass('mkb-disabled');
        $count.text(++dislikes);

        jQuery.ajax({
            method: 'POST',
            url: ajaxUrl,
            dataType: 'json',
            data: addAjaxNonce({
                action: 'mkb_article_dislike',
                id: id
            })
        }).done(function() {
            if (settings['track_article_dislikes']) {
                trackGoogleAnalytics(
                    settings['ga_dislike_category'],
                    settings['ga_dislike_action'],
                    settings['ga_dislike_label'] === 'article_title' ? title : id,
                    settings['ga_dislike_value'] || 0
                );
            }

            if (settings['show_dislike_message']) {
                $('.fn-rating-likes-block')
                    .html($('<div class="mkb-article-extra__message">' + i18n['dislike_message_text'] + '</div>'));
            }

            if (settings['enable_feedback'] &&
                (settings['feedback_mode'] === 'dislike' || settings['feedback_mode'] === 'any')) {
                addFeedbackForm();
            }
        });
    }

    /**
     * Renders feedback form if configured
     */
    function addFeedbackForm() {
        $('.fn-article-feedback-container').append($(
            '<div class="mkb-article-extra__feedback-form mkb-article-extra__feedback-form--no-content fn-feedback-form">' +
                '<div class="mkb-article-extra__feedback-form-title">' +
                i18n['feedback_label'] +
                '</div>' +
                '<div class="mkb-article-extra__feedback-form-message">' +
                '<textarea class="mkb-article-extra__feedback-form-message-area" rows="5"></textarea>' +
                (i18n['feedback_info_text'] ?
                    ('<div class="mkb-article-extra__feedback-info">' + i18n['feedback_info_text'] + '</div>') :
                    '') +
                '</div>' +
                '<div class="mkb-article-extra__feedback-form-submit">' +
                '<a href="#">' + i18n['feedback_submit_label'] + '</a>' +
                '</div>' +
            '</div>'
        ));
    }

    /**
     * Sends article feedback to server
     * @param e
     */
    function handleFeedbackSubmit(e) {
        var $trackingMeta = $('.mkb-article-extra__tracking-data');

        e.preventDefault();

        if (!$trackingMeta.length) {
            return;
        }

        var id = $trackingMeta.data('article-id');
        var title = $trackingMeta.data('article-title');
        var $btn = $(e.target);
        var $content = $('.mkb-article-extra__feedback-form-message-area');

        if (!id || !$content.val()) {
            return;
        }

        $btn
            .text(i18n['feedback_submit_request_label'])
            .attr('disabled', 'disabled');

        jQuery.ajax({
            method: 'POST',
            url: ajaxUrl,
            dataType: 'json',
            data: addAjaxNonce({
                action: 'mkb_article_feedback',
                id: id,
                content: $content.val()
            })
        }).done(function() {
            if (settings['track_article_feedback']) {
                trackGoogleAnalytics(
                    settings['ga_feedback_category'],
                    settings['ga_feedback_action'],
                    settings['ga_feedback_label'] === 'article_title' ? title : id,
                    settings['ga_feedback_value'] || 0
                );
            }

            $('.fn-article-feedback-container').html(
                '<div class="mkb-article-extra__feedback-sent-message">' +
                i18n['feedback_sent_text'] +
                '</div>'
            );
        });
    }

    /**
     * Toggle submit available
     * @param e
     */
    function handleFeedbackType(e) {
        $('.fn-feedback-form').toggleClass('mkb-article-extra__feedback-form--no-content', Boolean($(e.currentTarget).val() < 1));
    }

    /**
     * Back to top in articles
     */
    function handleArticleBackToTop() {
        var $container = $('.mkb-container');

        $container.on('click', '.mkb-back-to-top', function (e) {
            e.preventDefault();

            $doc.animate({
                scrollTop: $container.offset().top - adminOffset
            }, 300);
        });
    }

    /**
     * Article Table of Contents
     */
    function handleArticleTOC() {
        var $entryContent = $('.mkb-single-content');
        var $tocList = $('.mkb-anchors-list');
        var scrollOffset = parseInt(settings['toc_scroll_offset']['size']);
        var $headings;

        // dynamic TOC
        if ($tocList.hasClass('mkb-anchors-list--dynamic')) {
            $headings = $entryContent.find('h1, h2, h3, h4, h5, h6');

            if (settings['show_back_to_top']) {
                wrapTOCAnchors($headings);
            }

        } else { // via shortcodes
            $headings = $('.mkb-anchor__title');
        }

        // scroll
        var headingOffsets = Array.prototype.map.call($headings, function(heading) {
            return $(heading).offset().top;
        });
        var $links = $tocList.find('.mkb-anchors-list__item-link');
        var linksArr = Array.prototype.map.call($links, function(link) { return link; });

        function recalculateMetrics() {
            headingOffsets = Array.prototype.map.call($headings, function(heading) {
                return $(heading).offset().top;
            });
        }

        $(window).on('load', recalculateMetrics);
        $(window).on('resize', debounce(recalculateMetrics, 1000));

        setTimeout(recalculateMetrics, 3000); // in case load fails

        var navScrolling = false;

        // link click handlers
        $tocList.on('click', '.mkb-anchors-list__item-link', function (e) {
            var $item = $(e.currentTarget);
            var index = parseInt($item.data('index'), 10);

            e.preventDefault();

            navScrolling = true;

            if (settings['scrollspy_switch'] && settings['toc_in_content_disable']) {
                $links.removeClass('active');
                $item.addClass('active');
            }

            $doc.animate({
                scrollTop: headingOffsets[index] - scrollOffset
            }, 300, 'swing', function() { navScrolling = false; });
        });

        if (!settings['scrollspy_switch'] || !settings['toc_in_content_disable'] ||
            platform !== 'desktop' ||
            window.outerWidth < parseInt(settings['article_sidebar_sticky_min_width']['size'], 10)) {

            return;
        }

        // ScrollSpy
        var win = window;
        var doc = document.documentElement;

        $(win).on('scroll', throttle(350, function() {
            if (navScrolling) { return; }

            var top = win.pageYOffset || doc.scrollTop;

            linksArr.forEach(function(item, index) {
                var curr = headingOffsets[index] - scrollOffset - 1;
                var next = (index === headingOffsets.length - 1 ? 9999999 : headingOffsets[index + 1]) - scrollOffset - 1;

                $(item).toggleClass('active', top > curr && top < next);
            });
        }));
    }

    /**
     * Wraps headings n back to top containers when necessary
     * @param $headings
     */
    function wrapTOCAnchors($headings) {
        $headings.each(function(index, el) {
            var $heading = $(el);

            $heading.wrap('<div class="mkb-anchor mkb-clearfix mkb-back-to-top-' +
            settings['back_to_top_position'] +
            '"></div>');

            $heading.addClass('mkb-anchor__title');

            $heading.parent().append('<a href="#" class="mkb-back-to-top" title="' +
            settings['back_to_top_text'] + '">' +
            settings['back_to_top_text'] +
            (
                settings['show_back_to_top_icon'] ?
                '<i class="mkb-back-to-top-icon fa ' + settings['back_to_top_icon'] + '"></i>' :
                    ''
            ) +
            '</a>');
        });
    }

    /**
     * Articles fancy box
     */
    function initArticlesFancyBox() {
        // with captions
        $('figure[id^="attachment"] a').each(function (index, item) {
            var $item = $(item);
            var text = $item.parent().find('.wp-caption-text').text();

            $item.fancybox({
                titlePosition: 'over',
                title: text
            });
        });

        // no captions
        $('.mkb-single-content img').each(function(i, img) {
            var $img = $(img);
            var $link = $img.parent();

            if ($img.parents('figure.wp-caption').length || !$link.attr('href')) {
                return;
            }

            $link.fancybox({
                titlePosition: 'none',
                title: ''
            });
        });
    }

    /**
     * Search clear
     * @param e
     */
    function handleSearchClear(e) {
        e.preventDefault();

        $(e.currentTarget)
            .parents('.kb-search__input-wrap')
            .find('.kb-search__input')
            .val('')
            .trigger('input')
            .focus();
    }

    function initSearchInputs() {
        $kbSearch.each(function (index, el) {
            var $search = $(el);

            $search.on('input', debounce(
                onSearchType.bind(this, $search), parseInt(settings['search_delay'], 10) || 1000, false));
        });
    }

    /**
     * Detects if live search disabled for current platform
     * @returns {boolean}
     */
    function isSearchDisabled() {
        return Boolean(settings['live_search_disable_' + platform]);
    }

    /**
     * Sticky sidebar
     */
    function setupArticleStickySidebar() {

        if (!settings['article_sidebar_sticky'] ||
            !info.isSingle ||
            platform !== 'desktop' ||
            window.outerWidth < parseInt(settings['article_sidebar_sticky_min_width']['size'], 10)) {

            // sticky sidebar not enabled or not allowed
            return;
        }

        var sticky = false;
        var atBottom = false;
        var $sidebar = $('.mkb-sidebar');
        var sidebarHeight = $sidebar.outerHeight();
        var $root = $sidebar.parents('.mkb-root');
        var rootHeight = $root.outerHeight();
        var rootHeightInner = $root.height();
        var rootPad = rootHeight - rootHeightInner;
        var rootTop = $root.offset().top;
        var triggerPos = rootTop - rootPad / 2;
        var winHeight = window.innerHeight;
        var bottomOffset = winHeight > sidebarHeight + rootPad ? winHeight - sidebarHeight - rootPad : 0;
        var width = $sidebar.outerWidth();
        var win = window;
        var doc = document.documentElement;

        function recalculateMetrics() {
            rootHeight = $root.outerHeight();
            rootHeightInner = $root.height();
            rootPad = rootHeight - rootHeightInner;
            rootTop = $root.offset().top;
            triggerPos = rootTop - rootPad / 2;
            winHeight = window.innerHeight;
            sidebarHeight = $sidebar.outerHeight();
            bottomOffset = winHeight > sidebarHeight + rootPad ? winHeight - sidebarHeight - rootPad : 0;
        }

        $(win).on('load', recalculateMetrics);
        $(win).on('resize', debounce(recalculateMetrics, 1000));

        setTimeout(recalculateMetrics, 3000); // in case load fails

        $(win).on('scroll', function() {
            var top = win.pageYOffset || doc.scrollTop;
            var bottom = top + winHeight - bottomOffset;

            if (bottom > rootHeight + rootTop && !atBottom || bottom <= rootHeight + rootTop && atBottom) {
                atBottom = !atBottom;
                $sidebar.toggleClass('mkb-fixed-bottom', atBottom);
            }

            if (sticky && top >= triggerPos || !sticky && top < triggerPos) {
                return;
            }

            sticky = !sticky;
            $sidebar.toggleClass('mkb-fixed', sticky);
            $sidebar.css('max-width', sticky ? width + 'px' : 'none');
        });
    }

    function init() {
        var $body = $('body');

        if ($kbSearch.length && !isSearchDisabled()) {
            initSearchInputs();
            $body.on('keydown', onSearchKeyPress);
            $body.on('click', '.kb-search__clear', handleSearchClear);
            focusInput();
            onSearchType($kbSearch.eq(0)); // restore previous search
        }

        // article related code
        if (info.isSingle) {
            $body.on('click', '.mkb-article-extra__like', handleArticleLike);
            $body.on('click', '.mkb-article-extra__dislike', handleArticleDislike);
            $body.on('click', '.mkb-article-extra__feedback-form-submit', handleFeedbackSubmit);
            $body.on('input', '.mkb-article-extra__feedback-form-message-area', handleFeedbackType);

            handleArticleBackToTop();
            handleArticleTOC();
            initArticlesFancyBox();

            // single
            trackArticleView();

            // sticky articles sidebar
            setupArticleStickySidebar();
        }
    }

    // start
    $(document).ready(init);

})(jQuery);