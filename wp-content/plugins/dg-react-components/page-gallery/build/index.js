!function(e){var t={};function r(n){if(t[n])return t[n].exports;var o=t[n]={i:n,l:!1,exports:{}};return e[n].call(o.exports,o,o.exports,r),o.l=!0,o.exports}r.m=e,r.c=t,r.d=function(e,t,n){r.o(e,t)||Object.defineProperty(e,t,{enumerable:!0,get:n})},r.r=function(e){"undefined"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(e,"__esModule",{value:!0})},r.t=function(e,t){if(1&t&&(e=r(e)),8&t)return e;if(4&t&&"object"==typeof e&&e&&e.__esModule)return e;var n=Object.create(null);if(r.r(n),Object.defineProperty(n,"default",{enumerable:!0,value:e}),2&t&&"string"!=typeof e)for(var o in e)r.d(n,o,function(t){return e[t]}.bind(null,o));return n},r.n=function(e){var t=e&&e.__esModule?function(){return e.default}:function(){return e};return r.d(t,"a",t),t},r.o=function(e,t){return Object.prototype.hasOwnProperty.call(e,t)},r.p="",r(r.s=8)}([function(e,t){e.exports=window.wp.element},function(e,t){e.exports=window.wp.blockEditor},function(e,t){function r(){return e.exports=r=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var r=arguments[t];for(var n in r)Object.prototype.hasOwnProperty.call(r,n)&&(e[n]=r[n])}return e},e.exports.default=e.exports,e.exports.__esModule=!0,r.apply(this,arguments)}e.exports=r,e.exports.default=e.exports,e.exports.__esModule=!0},function(e,t){e.exports=function(e){if(null==e)throw new TypeError("Cannot destructure undefined")},e.exports.default=e.exports,e.exports.__esModule=!0},function(e,t){e.exports=function(e,t,r){return t in e?Object.defineProperty(e,t,{value:r,enumerable:!0,configurable:!0,writable:!0}):e[t]=r,e},e.exports.default=e.exports,e.exports.__esModule=!0},function(e,t){e.exports=window.wp.i18n},function(e,t){e.exports=window.wp.blocks},function(e,t){e.exports=window.wp.components},function(e,t,r){"use strict";r.r(t);var n=r(2),o=r.n(n),i=r(3),c=r.n(i),u=r(4),l=r.n(u),a=r(0),s=r(5),p=r(6),f=r(1),d=r(7);function b(e,t){var r=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),r.push.apply(r,n)}return r}function g(e){for(var t=1;t<arguments.length;t++){var r=null!=arguments[t]?arguments[t]:{};t%2?b(Object(r),!0).forEach((function(t){l()(e,t,r[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(r)):b(Object(r)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(r,t))}))}return e}Object(p.registerBlockType)("tcdi-components/page-gallery",{title:Object(s.__)("Child Pages Gallery","tcdi-components"),icon:"images-alt2",category:"tcdi-blocks",attributes:{count:{type:"number",default:3},height:{type:"number",default:400},width:{type:"number",default:800}},edit:Object(f.withColors)("backgroundColor",{textColor:"color"})((function(e){var t=e.attributes,r=t.width,n=t.height,o=e.toggleSelection,i=e.setAttributes,c=new URLSearchParams(window.location.search).get("post"),u=Object(f.useBlockProps)(),l="editing=true&parent=".concat(c),s={height:n+"px",width:r+"px"};return Object(a.createElement)("div",null,Object(a.createElement)(d.ResizableBox,{size:{height:n,width:r},style:{margin:"auto"},minHeight:"200",minWidth:"500",enable:{top:!1,right:!0,bottom:!0,left:!1,topRight:!1,bottomRight:!0,bottomLeft:!1,topLeft:!1},onResizeStop:function(e,t,c,u){i({height:parseInt(n+u.height,10),width:parseInt(r+u.width,10)}),o(!0)},onResizeStart:function(){o(!1)}},Object(a.createElement)("div",u,Object(a.createElement)("iframe",{width:r,height:n,style:g({},s),className:"",scrolling:"no",src:"https://tobacco.dgstg.org/#/en/embeddable/pagegallery?"+l}))))})),save:function(e){return c()(e.attributes),Object(a.createElement)("div",{className:{},style:{}},Object(a.createElement)("div",o()({},e.attributes,{className:"tcdi-component","data-component":"pageGallery"})))}})}]);