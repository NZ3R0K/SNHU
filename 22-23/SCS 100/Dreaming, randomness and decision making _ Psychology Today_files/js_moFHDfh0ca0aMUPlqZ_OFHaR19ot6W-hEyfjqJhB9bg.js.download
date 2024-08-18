/**
 * Javascript behavior for the Therapist Directory Search forms.
 */
(function ($) {
  $(document).ready(function () {
    var menuButton = $('.td-search--menu-button');
    var menu = $('.td-search--menu');
    var menuOption = $('.td-search--menu li');

    /**
     * Show the Menu when the button is clicked.
     */
    menuButton.click(function (e) {
      e.preventDefault();
      menu.show();
    });

    /**
     * When an option is selected update the form.
     */
    menuOption.click(function (e) {
      e.preventDefault();

      var selectedOptionText = $(this).children('a').data('selector-option-text');
      var selectedOptionUrl = $(this).children('a').data('selector-option-value');

      menuOption.removeClass('selected');
      $(this).addClass('selected');
      menuButton.text(selectedOptionText);
      $('#td_search_form').attr('action', selectedOptionUrl);

    });

    /**
     * Close all active menus when clicking outside of it.
     */
    $(document).click(function(e){
      if (!$(e.target).closest(menuButton).length) {
        menu.hide();
			}
    });
  });
})(jQuery);
;
