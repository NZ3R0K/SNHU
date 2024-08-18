/**
 * Javascript behavior for hiding large count items.
 */
(function () {

  var showLargeCountItems = function () {
    if (typeof(document.querySelectorAll("[data-show-large-count-items]")[0]) != 'undefined' && document.querySelectorAll("[data-show-large-count-items]")[0] != null) {
      document.querySelectorAll("[data-show-large-count-items]")[0].addEventListener("click", function (event) {
        event.preventDefault();
        event.stopPropagation();

        document.querySelectorAll("[data-hide-large-count-items]")[0].setAttribute("data-hide-large-count-items", "false");
      });
    }
  };

  if (
    document.readyState === "complete" ||
    (document.readyState !== "loading" && !document.documentElement.doScroll)
  ) {
    showLargeCountItems();
  } else {
    document.addEventListener("DOMContentLoaded", showLargeCountItems);
  }

})();
;
/**
 * Javascript behavior of the navbar.
 */
(function ($) {
  $(document).ready(function () {
    $('.main-nav--toggle-link').each(function ( index ) {
      $(this).on('click', function (e) {
        e.preventDefault();

        // The menu link that was clicked
        var $clickedLinkElement = $(this);

        // The panel we are interacting with.
        var $interactingPanel = $clickedLinkElement.siblings('.main-nav--panel');

        // If the panel we are interacting with is already active then we need
        // to make the panel inactive by returning it to the default state.
        if ($interactingPanel.hasClass('active')) {
          $clickedLinkElement.removeClass('active');
          $interactingPanel.removeClass('active').removeClass('d-block').addClass('d-none');
          $('body.main-nav-active').removeClass('main-nav-active');
        }
        else {

          // We are attempting to interact with another panel so we need
          // to make any active panels inactive.
          $('.main-nav--panel.active').removeClass('active').removeClass('d-block').addClass('d-none');
          $('.main-nav--toggle-link.active').removeClass('active');

          // We now make the panel we are interacting with active.
          $interactingPanel.addClass('active').addClass('d-block').removeClass('d-none');
          $clickedLinkElement.addClass('active');

          // We tell the body the menu is active.
          $('body').addClass('main-nav-active');
        }

        // If this is search, focus the search input
        if ($clickedLinkElement.parent().hasClass('main-nav--toggle--search')) {
          $clickedLinkElement.siblings().find('.main-nav--search-block-form__input').focus();
        }

      });
    });

    /**
     * Close all active menus when clicking outside of it.
     */
    $(document).click(function(e){
      if (!$(e.target).closest('.main-nav').length && $('body').hasClass('main-nav-active')) {
        $('.main-nav--panel.active').removeClass('active').removeClass('d-block').addClass('d-none');
        $('.main-nav--toggle-link.active').removeClass('active');
				$('body.main-nav-active').removeClass('main-nav-active');
			}
    });

  });
})(jQuery);
;
