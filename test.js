// run a simple burnin script. this doesn't really do anything
// other than do a bad job of checking if calling hide/show
// a lot will cause a segfault at some point

let count = 25000;

console.log(`Running ${count} iterations!`)
for ( let i = 0; i < count; i++ ) {
  var cursor = require('./index.js');
  cursor.hide();
  cursor.show();
}
console.log("Done!");