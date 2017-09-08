/**
 * Created by osumf on 4/24/2017.
 */

String.prototype.replaceAt=function(index, replacement) {
    return this.substr(0, index) + replacement+ this.substr(index + replacement.length);
};