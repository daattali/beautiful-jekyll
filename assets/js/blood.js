function createRandomMarginAnimation() {
    const drop = document.querySelector('.drop2');
    const maxWidth = window.innerWidth;
  
    // Generate random start and end points for the margin-left
    const startMargin = 0; //Math.random() * maxWidth;
    const endMargin = 400; //Math.random() * maxWidth;
  
    // Create dynamic keyframes for margin-left
    const styleSheet = document.styleSheets[0];
    const animationName = 'marginChange';
    const keyframes = `
      @keyframes ${animationName} {
        0% { margin-left: ${startMargin}px; }
        100% { margin-left: ${endMargin}px; }
      }
    `;
  
    // Append keyframes to the stylesheet
    styleSheet.insertRule(keyframes, styleSheet.cssRules.length);
  
    // Add the animation to the element
    drop.style.animation += `, ${animationName} 1.3s ease-in-out .5s infinite alternate`;
  }
  
  // Initialize the animation
  createRandomMarginAnimation();