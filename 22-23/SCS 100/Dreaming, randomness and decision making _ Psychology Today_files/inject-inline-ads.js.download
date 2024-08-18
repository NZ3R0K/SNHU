(function (window, $, Drupal, drupalSettings) {

  /**
   * AdInjectService constructor
   */
  function AdInjectService() {

    // Get ad settings from Drupal.settings object on page
    // Relevant drupalSettings data is set in pt_ad/AdsProcessedText.php
    this.adSettings = drupalSettings.ptAd;

    // Eject if we don't get any ads data from drupalSettings
    if (typeof this.adSettings === 'undefined') {
      return;
    }

    // Split off just the ad units from drupalSettings
    this.adUnits = this.adSettings.units;

    // Add the popFromObject method onto the adUnits object
    this.adUnits.pop = this.popFromObject;

    // Node type from drupalSettings
    this.pageType = this.adSettings.node_type;

    // Get all the body elements except half-width images, these are the
    // elements we use to determine ad spacing
    this.contentBodyElements = $('.field-name-body > *').not(':has(.image-article-inline-half)');

    // Get the total number of body elements that are not markup replacement
    // slots. Used to calculate "elements remaining" needed for ad insert rules
    this.totalNonSlotElements = this.contentBodyElements.not('.markup-replacement-slot').length;

    // vertical position of the bottom of the second sidebar ad, in-content ads
    // can only be inserted after this point.
    this.minimumVerticalOffset = $('#block-ad-blog-entry-300x600-right2-www-site .pt-ad--container').offset().top + 630;

    // Ad placement counter
    this.adsInserted = 0;

    // Initially set our validSlots variable
    this.validSlots = this.getValidSlots();

  }

  /**
   *
   * AdInjectService prototype
   *
   * We add shared methods on the prototype of AdInjectService so they get
   * shared by all instances of AdInjectService objects
   */

  AdInjectService.prototype = {
    constructor: AdInjectService,

    // Helper function to take the first item in an object, remove it from
    // the object and return it
    // Note: This has to actually be added to the object it will operate on,
    // ex:
    //    theObject.pop = this.popFromObject;
    // then you can call theObject.pop();
    popFromObject: function() {
      for (var key in this) {
        if (!Object.hasOwnProperty.call(this, key)) continue;
        if (key === 'pop') continue;
        var result = this[key];
        if (!delete this[key]) throw new Error();
        return result;
      }
    },

    // Function to get all the valid markup slots
    // This iterates through all body elements (except half-width images)
    // and pulls out all the markup slots along with data about their position
    // in the page
    //
    // Return Array of Objects
    // - The slot element itself
    // - Its vertical offset from top of window
    // - The vertical space between the top of the slot and the top of the previous
    // - The number of dom elements between the slot and the previous one
    //
    getValidSlots: function() {
      let validSlots = [];
      let elCount = 0;
      let spaceBetween = 0;
      let elementsRemaining = this.totalNonSlotElements;

      this.contentBodyElements.each( (i, el) => {

        var $element = $(el);

        var markupSlot = $element.hasClass('markup-replacement-slot');

        if (!markupSlot) {
          // Update el_counter for non-slots only since those don't display to user
          // and don't take up vertical space
          elCount++;

          // Update spaceBetween for non-slots only to get heights of content
          // elements, properly tracking the space between markup slots
          spaceBetween += $element.outerHeight(true);

          elementsRemaining--;
          // We updated our count and space tracking variables but since the
          // current element is NOT a markup slot we go no further and start
          // the loop over with the next element
          return;
        }

        // Find any slot that's after the sidebar ad in markup is valid
        var offset = $(el).offset().top;

        if (offset > this.minimumVerticalOffset) {

          validSlots.push({'element': el, 'offset': Math.floor(offset), 'spaceBetweenSlots': Math.floor(spaceBetween), 'elementsBetweenPreviousSlot': elCount, 'elementsRemaining': elementsRemaining});

          // after setting our valid slot data, reset counters and move on
          // to the next loop looking for the next markup slot
          elCount = 0;
          spaceBetween = 0;

        } else {
          // If the markup slot appears above the sidebar ad, do nothing
          return;
        }

      });

      return validSlots;
    },

    // Run through all validSlots, make sure there are ads to place, then
    // place them using desktop spacing rules
    placeInlineDesktopAds: function() {

      var elementCount = 0;
      var spaceBetween = 0;

      $.each(this.validSlots, (index, el) => {

        // Make sure we only act on real array elements
        if (typeof el === 'undefined') {
          return;
        }

        // Stop iterating if 4 ads have been placed
        if (this.adsInserted >= 4) {
          return false;
        }

        // Don't place any more ads if fewer than 2 body elements remain
        if (el.elementsRemaining <= 2) {
          return false;
        }

        // Update counters with data from the new slot
        spaceBetween += el.spaceBetweenSlots;
        elementCount += el.elementsBetweenPreviousSlot;

        if (elementCount > 2 && spaceBetween > 750) {

          // Actually place the ad into the slot if we have an ad remaining
          this.insertMarkupIntoSlot(el.element, this.adUnits.pop());

          // Remove the slot we use from validSlots array so future elements
          // can't try to insert into it
          this.validSlots.splice(index, 1);

          // The slot has been filled, so reset counters for next ad placement
          elementCount = 0;
          spaceBetween = 0;
        }

      });

    },

    // Tablet slot placement simply uses the slot index provided in drupalSettings
    placeInlineTabletAds: function() {
      $.each(this.adUnits, (index, el) => {
        let slotClass = '.markup-replacement-slot-' + index;
        this.insertMarkupIntoSlot(slotClass, el);
      });
    },

    // Helper to replace a markup slot with markup
    insertMarkupIntoSlot: function(elementSelectorToReplace, markup) {
      let $slot = $(elementSelectorToReplace);
      if ($slot.length) {
        $slot.replaceWith(markup);
        this.adsInserted++;
      }
    }

  };

  function createAdService() {
    /**
     * And finally, instantiate AdInjectService for the page this js loads on
     * @type {AdInjectService}
     */
    const adService = new AdInjectService();

    if (window.innerWidth > 991) {
      adService.placeInlineDesktopAds();
    } else {
      adService.placeInlineTabletAds();
    }
  }

  /**
   * Process the ad slots.
   */
  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", function() {
      createAdService();
    });
  } else {
    createAdService();
  }

})(window, jQuery, Drupal, drupalSettings);
