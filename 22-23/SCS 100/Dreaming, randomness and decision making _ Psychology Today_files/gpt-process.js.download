( function( window, drupalSettings ) {

  /**
   * Initiate googletag.
   * @type {*|{cmd: []}}
   */
  window.googletag = window.googletag || {cmd: []};

  /**
   * Constant representing the small device width.
   * @type {number}
   */
  const smallWidth = 768;

  /**
   * Constant representing the medium device width.
   * @type {number}
   */
  const mediumWidth = 992;

  /**
   * Constant representing the large device width.
   * @type {number}
   */
  const largeWidth = 1200;

  /**
   * Variable representing the ad units.
   * @type {Array}
   */
  let units = [];

  /**
   * Variable representing the ad slot values.
   * @type {Array}
   */
  let slotValues = [];

  /**
   * Helper function to determine if the screen is small.
   * @returns {boolean}
   */
  function isSmallScreen() {
    return (window.innerWidth <= smallWidth);
  }

  /**
   * Helper function to determine if the screen is medium.
   * @returns {boolean}
   */
  function isMediumScreen() {
    return (window.innerWidth > smallWidth && window.innerWidth <= mediumWidth);
  }

  /**
   * Helper function to determine if the screen is large.
   * @returns {boolean}
   */
  function isLargeScreen() {
    return (window.innerWidth > mediumWidth && window.innerWidth <= largeWidth);
  }

  /**
   * Helper function to determine if the screen is extra_large.
   * @returns {boolean}
   */
  function isExtraLargeScreen() {
    return (window.innerWidth > largeWidth);
  }

  /**
   * Set up global targeting.
   */
  function gptTargeting(googletag) {
    // Get the targets from Drupal.
    var targets = drupalSettings.ptAd.slotPlacement.targets.targeting;

    // Add targeting.
    for (var key in targets) {
      if (targets.hasOwnProperty(key)) {
        var value = targets[key];
        googletag.pubads().setTargeting(key, value);
      }
    }
  }

  /**
   * Sets global exclusions to ad categories that PT does not want Google to display.
   * See: https://support.google.com/admanager/answer/3238504
   */
  function gptCategoryExclusions(googletag){
    var exclusions = drupalSettings.ptAd.slotPlacement.exclusions;
    for (var key in exclusions) {
       googletag.pubads().setCategoryExclusion(exclusions[key]);
    }
  }

  /**
   * Push Google Tag slot
   */
  function pushSlot(googletag, slot) {
    return googletag
      .defineSlot(slot.path, slot.size, slot.opt_div)
      .addService(googletag.pubads());
  }

  /**
   * Push Google Tag slot
   */
  function gptAddSlotListeners(googletag) {
    let addLoadedClass = function (slot) {
      let adContentContainer = document.getElementById(slot.opt_div);
      if (adContentContainer !== null) {
        adContentContainer.classList.add("ad--content-loaded");
      }
    };

    googletag.cmd.push(function () {
      for (const slot of slotValues) {
        googletag
          .pubads().addEventListener("slotRenderEnded", function() {
          addLoadedClass(slot);
        });
      }
    });
  }

  /**
   * Define ad slots.
   */
  function gptDefineSlots(googletag) {
    // Get the slots from Drupal.
    const slots = drupalSettings.ptAd.slotPlacement.slots;
    slotValues = Object.values(slots);

    // Define slots.
    for (const slot of slotValues) {
      if (isSmallScreen() && slot.display_small) {
        units.push(pushSlot(googletag, slot));
      }
      if (isMediumScreen() && slot.display_medium) {
        units.push(pushSlot(googletag, slot));
      }
      if (isLargeScreen() && slot.display_large) {
        units.push(pushSlot(googletag, slot));
      }
      if (isExtraLargeScreen() && slot.display_extra_large) {
        units.push(pushSlot(googletag, slot));
      }
    }

    googletag.pubads().refresh(units);
  }

  /**
   * Add global targeting and define slots in the recommended documentation order.
   * @see https://developers.google.com/doubleclick-gpt/common_implementation_mistakes
   */
  function gptProcess(googletag) {
    googletag.cmd.push(function () {
      googletag.pubads().disableInitialLoad();
      googletag.pubads().enableSingleRequest();
      googletag.pubads().enableLazyLoad();
      googletag.enableServices();

      // Add page-level targeting.
      gptTargeting(googletag);

      // Add page-level exclusions.
      gptCategoryExclusions(googletag);

      // Define slots.
      gptDefineSlots(googletag);

      // Add slot listeners.
      gptAddSlotListeners(googletag);
    });
  }

  /**
   * Process the ad slots.
   */
  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", function() {
      gptProcess(window.googletag);
    });
  } else {
    gptProcess(window.googletag);
  }

})(window, drupalSettings);
