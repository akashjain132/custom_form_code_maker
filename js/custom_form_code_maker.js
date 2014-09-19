(function ($) {
Drupal.behaviors.autosave_taxonomy = {
  attach: function (context, settings) {
    jQuery(document).ready(function() {
      $('.ajax-element-field').change(function() {
        if ($(this).is(':checked')) {
    	    $(this).parents('fieldset').find('.ajax-callback-field').parents('.form-item').show();
    	    $(this).parents('fieldset').find('.ajax-wrapper-field').parents('.form-item').show();
    	    $(this).parents('fieldset').find('.ajax-method-field').parents('.form-item').show();
    	  }
    	  else {
    	    $(this).parents('fieldset').find('.ajax-callback-field').parents('.form-item').hide();
    	    $(this).parents('fieldset').find('.ajax-wrapper-field').parents('.form-item').hide();
    	    $(this).parents('fieldset').find('.ajax-method-field').parents('.form-item').hide();
    	  }
      });
    });
  }};

})(jQuery);
