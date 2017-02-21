
$(function() {
  $(document).on('can_embed_loaded',
    function() {
      /*** IT'S TIME TO DO OUR CALL TO ACTION PUSH ***/
      if (location.search && location.search.toLowerCase().indexOf("?signup") === 0) {
        $('#email-signup-wrapper').addClass('signup-emphasize-form');
      } // end if
    } // end function
  );
  $(document).on('can_embed_submitted',
    function() {

    } // end function
  );
});
