const R = require('ramda');
const got = require('got');
const T = require('terminal-image');
const fs = require('fs');
const flickrDataDog = JSON.parse(fs.readFileSync('dogs.json', 'utf8'));


/* ********************************************************************************************** */
/* ****************************          Predicate  Methods           *************************** */
/* ********************************************************************************************** */
// Check if value of x is 0. Return true if x is 0, false otherwise.
const isZero = x => x === 0;

// Check if value of the input is Alphanumeric. Return true if it is, false otherwise.
const isAlphaNumeric = R.compose(isZero, R.length(), R.match(/[^a-zA-Z0-9]/g));

// Compare to string (Commonly used for sorting strings). Return true string a is less than string
// b, false otherwise.
const compareStrings = R.comparator((a, b) => a < b);


/* ********************************************************************************************** */
/* ****************************            Helper Methods             *************************** */
/* ********************************************************************************************** */
// Takes input of 1 or more string object separated by spaces (like the tags of the flickr data) in
// arrays, and turns them into an array of single word string objects.
const combineStringArray = R.compose(
  R.split(' '),
  R.join(' '),
);

/* ********************************************************************************************** */
/* **************************** Filtering Properties From Flickr JSON *************************** */
/* ********************************************************************************************** */
// Returns the array of objects in the item property
const flickrImageData = R.compose(
  R.prop('items'),
);

/* ********************************************************************************************** */
/* ****************************         Project code                  *************************** */
/* ********************************************************************************************** */

// Checks to make sure selected image input is in bounds and returns
const getImage = (x) => {
    if(x >= 0 && x < 20) // checks if input is between 1 and 20
        return x;
    else return 0; // If out of bounds return 0
}

// Used to extract the url from the relevant dog file
const imageID = R.pipe(
  flickrImageData,
  R.nth(getImage(process.argv[2])),
  R.prop('media'),
  R.prop('m')
);


(async () =>{
    const {body} = await got(imageID(flickrDataDog), {encoding: null});
    console.log(await T.buffer(body));
})();
