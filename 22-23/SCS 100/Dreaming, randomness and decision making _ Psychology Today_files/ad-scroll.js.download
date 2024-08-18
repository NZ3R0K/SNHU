(function (window, $) {

  var adContentLoopTimer;
  var adFrameLoopTimer;
  var adChildFrameLoopTimer;
  var loopTimeout = 300;
  var debounceDelay = 15;

  function debounce(method, delay) {
    clearTimeout(method._tId);
    method._tId= setTimeout(function(){
      method();
    }, delay);
  }

  // Setup adjusting of ad based on scroll position
  function adjustAd(scroll_pos, ad, page_top, ad_container_top) {
    // Code for scrolling FIRST ad unit on Blog Entry page
    // Only activate ad scrolling on sidebar ads that are 300x250
    // with 'Advertisement' label, ad height is 275px.
    var ad_height = ad.innerHeight();

    if (ad_height !== undefined && ad_height > 0) {
      if (ad_height <= 278) {
        if ((scroll_pos + page_top) >= ad_container_top && (scroll_pos + page_top) <= (ad_container_top + 350)) {
          ad.css({
            "position": "fixed",
            "top": page_top,
            "width": "300px"
          });
        }
        else if ((scroll_pos + page_top) >= (ad_container_top + 351)) {
          ad.css({
            "position": "relative",
            "top": "351px",
          });
        }
        else {
          ad.css({
            "position": "relative",
            "top": "",
            "width": ""
          });
        }
      }
    }
  }

  // Check if ad child iframe has loaded, recheck if not.
  function checkAdChildFrameLoaded(scroll_pos, ad, ad_iframe, page_top, ad_container_top) {
    if (ad_iframe.attr("data-load-complete") === "true") {
      if (adFrameLoopTimer !== null) {
        clearInterval(adChildFrameLoopTimer);
      }
      adjustAd(scroll_pos, ad, page_top, ad_container_top);
    } else if (adChildFrameLoopTimer === null) {
      adChildFrameLoopTimer = setInterval(
        checkAdChildFrameLoaded(scroll_pos, ad, ad_iframe, page_top, ad_container_top),
        loopTimeout
      );
    }
  }

  // Check if ad iframe has loaded, recheck if not.
  function checkAdFrameLoaded(scroll_pos, ad, ad_iframe, page_top, ad_container_top) {
    if (ad_iframe.attr("data-load-complete") === "true") {
      if (adFrameLoopTimer !== null) {
        clearInterval(adFrameLoopTimer);
      }
      var child_iframe = ad_iframe.contents().find("iframe");
      if (child_iframe.length > 0) {
        checkAdChildFrameLoaded(scroll_pos, ad, child_iframe, page_top, ad_container_top);
      } else {
        adjustAd(scroll_pos, ad, page_top, ad_container_top);
      }
    } else if (adFrameLoopTimer === null) {
      adFrameLoopTimer = setInterval(
        checkAdFrameLoaded(scroll_pos, ad, ad_iframe, page_top, ad_container_top),
        loopTimeout
      );
    }
  }

  // Check if ad has loaded, recheck if not.
  function checkAdLoaded(scroll_pos, ad, ad_content, page_top, ad_container_top) {
    if (ad_content.hasClass("ad--content-loaded")) {
      if (adContentLoopTimer !== null) {
        clearInterval(adContentLoopTimer);
      }
      var ad_iframe = ad.find("iframe");
      checkAdFrameLoaded(scroll_pos, ad, ad_iframe, page_top, ad_container_top);
    } else if (adContentLoopTimer === null) {
      adContentLoopTimer = setInterval(
        checkAdLoaded(scroll_pos, ad, ad_content, page_top, ad_container_top),
        loopTimeout
      );
    }
  }

  // Setup ad scrolling function for 250x300 sidebar ads
  function adscroll_250(scroll_pos) {

    // Set page top space.
    var page_top =  79;

    // Setup variables we'll need to ad scrolling for Blog Entry ad units
    var ad_container = $(".pt-ad--scroll");
    var ad_container_top = 0;
    if (ad_container.length) {
      ad_container_top = ad_container.offset().top;
    }
    var ad = ad_container.find(".pt-ad--container");
    var ad_content = ad.find(".pt-ad--content");

    checkAdLoaded(
      scroll_pos,
      ad,
      ad_content,
      page_top,
      ad_container_top
    );
  } // end adscroll_250

  // Function for getting page scroll position
  function getScrollTop() {
    if (typeof window.pageYOffset !== 'undefined' ) {
      // Most browsers
      return window.pageYOffset;
    }

    var d = document.documentElement;
    if (d.clientHeight) {
      // IE in standards mode
      return d.scrollTop;
    }

    // IE in quirks mode
    return document.body.scrollTop;
  }

  // Function for handling the scrolling behavior
  function handleScroll() {
    // Update scroll position tracker
    var scroll_pos = getScrollTop();

    // Make sure the right ads are loaded on the page before executing the js
    if ($(".pt-ad--scroll").length) {
      // Pass the right node type selector
      adscroll_250(scroll_pos);
    }
  }

  /**
   * Script for making Blog Entry ads scroll with page
   * We'll set ad to fixed position fixed when it hits the top of page and has
   * scrolled less the available height of its scrolling 'runway'
   */
  if (window.innerWidth >= 992) {
    // This code runs as the user scrolls
    window.onscroll = function() {
      debounce(handleScroll, debounceDelay);
    }; // End Ad Scrolling code
  }

})(window, jQuery);
