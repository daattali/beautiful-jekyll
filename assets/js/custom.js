document.addEventListener('DOMContentLoaded', function() {
  // Remove "Powered by" text
  const footerText = document.querySelector('footer p.theme-by');
  if (footerText) {
    footerText.style.display = 'none';
  }

  // Hide social links on non-home pages
  if (window.location.pathname !== '/') {
    const socialLinks = document.querySelector('footer .social-links');
    if (socialLinks) {
      socialLinks.style.display = 'none';
    }
  }
});
