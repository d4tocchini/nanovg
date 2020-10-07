//
// Copyright (c) 2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef NANOVG_H
#define NANOVG_H

#define VG_API

#define STB_IMAGE__H 		"stb/stb_image.h"
#define STB_IMAGE_WRITE__H 	"stb/stb_image_write.h"
#define STB_TRUETYPE__H 	"stb/stb_truetype.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NVG_PI 3.14159265358979323846264338327f

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
#endif

#define NVGcontext				vg_t
typedef struct vg_t 			vg_t;

//
// Frame
//
#define nvgBeginFrame			vg_frame_begin
#define nvgCancelFrame			vg_frame_cancel
#define nvgEndFrame				vg_frame_end

//
// State Stack
//	* transform
//	* fill & stroke style
//	* text & font styles
// 	* scissor clipping.
//
#define nvgSave 				vg_push
#define nvgRestore 				vg_pop
#define nvgReset 				vg_reset

//
// Color
//
#define	NVGcolor				vg_color_t
typedef struct vg_color_t 		vg_color_t;
struct vg_color_t {
	union {
		float rgba[4];
		struct {
			float r,g,b,a;
		};
	};
};
#define nvgRGB					vg_rgb
#define nvgRGBA					vg_rgba
#define nvgRGBf					vg_rgb_f
#define nvgRGBAf				vg_rgba_f
#define nvgHSL					vg_hsl
#define nvgHSLA					vg_hsla
#define nvgTransRGBA			vg_color_alpha
#define nvgTransRGBAf			vg_color_alpha_f
#define nvgLerpRGBA				vg_color_mix

//
// Paints
//
#define NVGpaint				vg_paint_t
typedef struct vg_paint_t 		vg_paint_t;
struct vg_paint_t {
	float xform[6];
	float extent[2];
	float radius;
	float feather;
	vg_color_t innerColor;
	vg_color_t outerColor;
	int image;
};
#define nvgImagePattern			vg_img_pattern
#define nvgLinearGradient		vg_gradient
#define nvgBoxGradient			vg_gradient_box
#define nvgRadialGradient		vg_gradient_rad

//
// Render styles
//
#define NVGlineCap				vg_line_cap_t
enum vg_line_cap_t {
	NVG_BUTT,
	NVG_ROUND,
	NVG_SQUARE,
	NVG_BEVEL,
	NVG_MITER,
};
#define nvgShapeAntiAlias		vg_aa
#define nvgStrokeColo			vg_stroke_color
#define nvgStrokePaint			vg_stroke_paint
#define nvgFillColor			vg_fill_color
#define nvgFillPaint			vg_fill_paint
#define nvgStrokeWidth			vg_stroke_w
#define nvgMiterLimit			vg_miter_limit
#define nvgLineCap				vg_line_cap
#define nvgLineJoin				vg_line_join
#define nvgGlobalAlpha			vg_global_alpha

//
// Paths
//
#define nvgBeginPath			vg_path
#define nvgClosePath			vg_closepath
//
#define nvgMoveTo				vg_moveto
#define nvgLineTo				vg_lineto
#define nvgBezierTo				vg_bezto
#define nvgQuadTo				vg_qbezto
#define nvgArcTo				vg_arcto
//
#define nvgRect					vg_rect
#define nvgRoundedRect			vg_rrect
#define nvgRoundedRectVarying	vg_rrectv
#define nvgEllipse				vg_ellipse
#define nvgCircle				vg_circle
#define nvgArc					vg_arc
//
#define nvgFill					vg_fill
#define nvgStroke				vg_stroke
// winding
#define nvgPathWinding			vg_path_winding
#define NVGwinding				vg_winding_t
#define NVGsolidity				vg_solidity_t
enum vg_winding_t {
	NVG_CCW = 1,			// Winding for solid shapes
	NVG_CW = 2,				// Winding for holes
};
enum vg_solidity_t {
	NVG_SOLID = 1,			// CCW
	NVG_HOLE = 2,			// CW
};

//
// Scissoring
//
#define nvgScissor				vg_clip
#define nvgIntersectScissor		vg_clip_intersect
#define nvgResetScissor			vg_clip_reset

//
// Text
//
#define nvgCreateFont			vg_font_create
#define nvgFontFace				vg_font_name
#define nvgFontFaceId			vg_font_id
#define nvgFontSize				vg_font_size
#define nvgFontBlur				vg_font_blur
#define nvgText					vg_text
#define nvgTextLineHeight		vg_text_lineh
#define nvgTextAlign			vg_text_align
#define nvgTextLetterSpacing	vg_text_tracking
#define nvgTextBounds			vg_text_bounds
#define nvgTextGlyphPositions	vg_text_h_metrics
#define nvgTextMetrics			vg_text_v_metrics
#define nvgTextBreakLines		vg_text_to_lines
#define nvgTextBox				vg_textbox
#define nvgTextBoxBounds		vg_textbox_bounds
#define NVGalign				vg_align_t
enum vg_align_t {
	// Horizontal align
	NVG_ALIGN_LEFT 		= 1<<0,	// Default, align text horizontally to left.
	NVG_ALIGN_CENTER 	= 1<<1,	// Align text horizontally to center.
	NVG_ALIGN_RIGHT 	= 1<<2,	// Align text horizontally to right.
	// Vertical align
	NVG_ALIGN_TOP 		= 1<<3,	// Align text vertically to top.
	NVG_ALIGN_MIDDLE	= 1<<4,	// Align text vertically to middle.
	NVG_ALIGN_BOTTOM	= 1<<5,	// Align text vertically to bottom.
	NVG_ALIGN_BASELINE	= 1<<6, // Default, align text vertically to baseline.
};
#define NVGglyphPosition			vg_text_h_metrics_t
typedef struct vg_text_h_metrics_t 	vg_text_h_metrics_t;
struct vg_text_h_metrics_t {
	const char* str;	// Position of the glyph in the input string.
	float x;			// The x-coordinate of the logical glyph position.
	float minx, maxx;	// The bounds of the glyph shape.
};
#define NVGtextRow				vg_text_row_t
typedef struct vg_text_row_t 	vg_text_row_t;
struct vg_text_row_t {
	const char* start;	// Pointer to the input text where the row starts.
	const char* end;	// Pointer to the input text where the row ends (one past the last character).
	const char* next;	// Pointer to the beginning of the next row.
	float width;		// Logical width of the row.
	float minx, maxx;	// Actual bounds of the row. Logical with and bounds can differ because of kerning and some parts over extending.
};


//
// Composite operation
//
#define vg_comp_op			nvgGlobalCompositeOperation
#define vg_comp_blend		nvgGlobalCompositeOperation
#define vg_comp_blend_sep	nvgGlobalCompositeBlendFuncSeparate
enum NVGblendFactor {
	NVG_ZERO = 1<<0,
	NVG_ONE = 1<<1,
	NVG_SRC_COLOR = 1<<2,
	NVG_ONE_MINUS_SRC_COLOR = 1<<3,
	NVG_DST_COLOR = 1<<4,
	NVG_ONE_MINUS_DST_COLOR = 1<<5,
	NVG_SRC_ALPHA = 1<<6,
	NVG_ONE_MINUS_SRC_ALPHA = 1<<7,
	NVG_DST_ALPHA = 1<<8,
	NVG_ONE_MINUS_DST_ALPHA = 1<<9,
	NVG_SRC_ALPHA_SATURATE = 1<<10,
};
enum NVGcompositeOperation {
	NVG_SOURCE_OVER,
	NVG_SOURCE_IN,
	NVG_SOURCE_OUT,
	NVG_ATOP,
	NVG_DESTINATION_OVER,
	NVG_DESTINATION_IN,
	NVG_DESTINATION_OUT,
	NVG_DESTINATION_ATOP,
	NVG_LIGHTER,
	NVG_COPY,
	NVG_XOR,
};
struct NVGcompositeOperationState {
	int srcRGB;
	int dstRGB;
	int srcAlpha;
	int dstAlpha;
};
typedef struct NVGcompositeOperationState NVGcompositeOperationState;


//
// Images
//
enum NVGimageFlags {
    NVG_IMAGE_GENERATE_MIPMAPS	= 1<<0,     // Generate mipmaps during creation of the image.
	NVG_IMAGE_REPEATX			= 1<<1,		// Repeat image in X direction.
	NVG_IMAGE_REPEATY			= 1<<2,		// Repeat image in Y direction.
	NVG_IMAGE_FLIPY				= 1<<3,		// Flips (inverses) image in Y direction when rendered.
	NVG_IMAGE_PREMULTIPLIED		= 1<<4,		// Image data has premultiplied alpha.
	NVG_IMAGE_NEAREST			= 1<<5,		// Image interpolation is Nearest instead Linear
};
#define nvgCreateImage          vg_img_create
#define nvgCreateImageRGBA      vg_img_from
#define nvgUpdateImage          vg_img_update
#define nvgImageSize            vg_img_size
#define nvgDeleteImage			vg_img_free
// 								vg_img_delete

//
// Frame
//
// Calls to nanovg drawing API should be wrapped in nvgBeginFrame() & nvgEndFrame()
// nvgBeginFrame() defines the size of the window to render to in relation currently
// set viewport (i.e. glViewport on GL backends). Device pixel ration allows to
// control the rendering on Hi-DPI devices.
// For example, GLFW returns two dimension for an opened window: window size and
// frame buffer size. In that case you would set windowWidth/Height to the window size
// devicePixelRatio to: frameBufferWidth / windowWidth.

VG_API 	void nvgBeginFrame(vg_t* ctx, float windowWidth, float windowHeight, float devicePixelRatio);
VG_API 	void nvgCancelFrame(vg_t* ctx);
VG_API 	void nvgEndFrame(vg_t* ctx);

//
// Composite operation
//
// The composite operations in NanoVG are modeled after HTML Canvas API, and
// the blend func is based on OpenGL (see corresponding manuals for more info).
// The colors in the blending state have premultiplied alpha.

		// Sets the composite operation. The op parameter should be one of NVGcompositeOperation.
VG_API 	void nvgGlobalCompositeOperation(vg_t* ctx, int op);

		// Sets the composite operation with custom pixel arithmetic. The parameters should be one of NVGblendFactor.
VG_API 	void nvgGlobalCompositeBlendFunc(vg_t* ctx, int sfactor, int dfactor);
VG_API 	void nvgGlobalCompositeBlendFuncSeparate(vg_t* ctx, int srcRGB, int dstRGB, int srcAlpha, int dstAlpha);

//
// Color utils
//
// Colors in NanoVG are stored as unsigned ints in ABGR format.

		// int8 r,g,b,a
VG_API 	vg_color_t nvgRGB(unsigned char r, unsigned char g, unsigned char b); // a = 255
VG_API 	vg_color_t nvgRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		// float r,g,b,a
VG_API 	vg_color_t nvgRGBf(float r, float g, float b); // a = 1.0f
VG_API 	vg_color_t nvgRGBAf(float r, float g, float b, float a);
		// float h,s,l , int8 a
VG_API 	vg_color_t nvgHSL(float h, float s, float l); // a = 255
VG_API 	vg_color_t nvgHSLA(float h, float s, float l, unsigned char a);
		// Sets transparency of a color value.
VG_API 	vg_color_t nvgTransRGBA(vg_color_t c0, unsigned char a);
VG_API 	vg_color_t nvgTransRGBAf(vg_color_t c0, float a);
		// Linearly interpolates from color c0 to c1, and returns resulting color value.
VG_API 	vg_color_t nvgLerpRGBA(vg_color_t c0, vg_color_t c1, float u);


//
// State Handling
//
// The state which represents how paths will be rendered:
//		* transform
//		* fill & stroke style
//		* text & font styles
//		* scissor clipping.

		// Pushes and saves the current render state onto stack. (matching nvgRestore() must be used to restore the state)
VG_API	void nvgSave(vg_t* ctx);
		// Pops and restores current render state.
VG_API	void nvgRestore(vg_t* ctx);
		// Resets current render state to default vals. Does not affect the render state stack.
VG_API	void nvgReset(vg_t* ctx);

//
// Render styles
//
// Fill and stroke render style can be either a solid color or a paint which is a gradient or a pattern.
// Solid color is simply defined as a color value, different kinds of paints can be created
// using nvgLinearGradient(), nvgBoxGradient(), nvgRadialGradient() and nvgImagePattern().
//
// Current render style can be saved and restored using nvgSave() and nvgRestore().

		// Sets the transparency applied to all rendered shapes. (Already transparent paths will get proportionally more transparent)
VG_API 	void nvgGlobalAlpha(vg_t* ctx, float alpha);
		// Sets whether to draw antialias for nvgStroke() and nvgFill(). It's enabled by default.
VG_API	void nvgShapeAntiAlias(vg_t* ctx, int enabled);
		// Sets current stroke style to solid color.
VG_API 	void nvgStrokeColor(vg_t* ctx, vg_color_t color);
		// Sets current stroke style to a paint, which can be a one of the gradients or a pattern.
VG_API 	void nvgStrokePaint(vg_t* ctx, NVGpaint paint);
		// Sets current fill style to solid color.
VG_API 	void nvgFillColor(vg_t* ctx, vg_color_t color);
		// Sets current fill style to a paint, which can be a one of the gradients or a pattern.
VG_API 	void nvgFillPaint(vg_t* ctx, NVGpaint paint);
		// Sets the miter limit of stroke style (controls when a sharp corner is beveled)
VG_API 	void nvgMiterLimit(vg_t* ctx, float limit);
		// Sets the stroke width of the stroke style.
VG_API 	void nvgStrokeWidth(vg_t* ctx, float size);
		// Sets how end of the line is drawn: NVG_BUTT (default), NVG_ROUND, NVG_SQUARE
VG_API 	void nvgLineCap(vg_t* ctx, int cap);
		// Sets how sharp path corners are drawn: NVG_MITER (default), NVG_ROUND, NVG_BEVEL.
VG_API 	void nvgLineJoin(vg_t* ctx, int join);


//
// Transforms
//
// The paths, gradients, patterns and scissor region are transformed by an transformation
// matrix at the time when they are passed to the API.
// The current transformation matrix is a affine matrix:
//   [sx kx tx]
//   [ky sy ty]
//   [ 0  0  1]
// Where: sx,sy define scaling, kx,ky skewing, and tx,ty translation.
// The last row is assumed to be 0,0,1 and is not stored.
//
// Apart from nvgResetTransform(), each transformation function first creates
// specific transformation matrix and pre-multiplies the current transformation by it.
//
// Current coordinate system (transformation) can be saved and restored using nvgSave() and nvgRestore().

// Resets current transform to a identity matrix.
VG_API 	void nvgResetTransform(vg_t* ctx);

// Premultiplies current coordinate system by specified matrix.
// The parameters are interpreted as matrix as follows:
//   [a c e]
//   [b d f]
//   [0 0 1]
VG_API	void nvgTransform(vg_t* ctx, float a, float b, float c, float d, float e, float f);

// Translates current coordinate system.
VG_API	void nvgTranslate(vg_t* ctx, float x, float y);

// Rotates current coordinate system. Angle is specified in radians.
VG_API	void nvgRotate(vg_t* ctx, float angle);

// Skews the current coordinate system along X axis. Angle is specified in radians.
VG_API	void nvgSkewX(vg_t* ctx, float angle);

// Skews the current coordinate system along Y axis. Angle is specified in radians.
VG_API	void nvgSkewY(vg_t* ctx, float angle);

// Scales the current coordinate system.
VG_API	void nvgScale(vg_t* ctx, float x, float y);

// Stores the top part (a-f) of the current transformation matrix in to the specified buffer.
//   [a c e]
//   [b d f]
//   [0 0 1]
// There should be space for 6 floats in the return buffer for the values a-f.
VG_API	void nvgCurrentTransform(vg_t* ctx, float* xform);


// The following functions can be used to make calculations on 2x3 transformation matrices.
// A 2x3 matrix is represented as float[6].

// Sets the transform to identity matrix.
VG_API	void nvgTransformIdentity(float* dst);

// Sets the transform to translation matrix matrix.
VG_API	void nvgTransformTranslate(float* dst, float tx, float ty);

// Sets the transform to scale matrix.
VG_API	void nvgTransformScale(float* dst, float sx, float sy);

// Sets the transform to rotate matrix. Angle is specified in radians.
VG_API	void nvgTransformRotate(float* dst, float a);

// Sets the transform to skew-x matrix. Angle is specified in radians.
VG_API	void nvgTransformSkewX(float* dst, float a);

// Sets the transform to skew-y matrix. Angle is specified in radians.
VG_API	void nvgTransformSkewY(float* dst, float a);

// Sets the transform to the result of multiplication of two transforms, of A = A*B.
VG_API	void nvgTransformMultiply(float* dst, const float* src);

// Sets the transform to the result of multiplication of two transforms, of A = B*A.
VG_API	void nvgTransformPremultiply(float* dst, const float* src);

// Sets the destination to inverse of specified transform.
// Returns 1 if the inverse could be calculated, else 0.
VG_API	int nvgTransformInverse(float* dst, const float* src);

// Transform a point by given transform.
VG_API	void nvgTransformPoint(float* dstx, float* dsty, const float* xform, float srcx, float srcy);

// Converts degrees to radians and vice versa.
VG_API	float nvgDegToRad(float deg);
VG_API	float nvgRadToDeg(float rad);

//
// Images
//
// NanoVG allows you to load jpg, png, psd, tga, pic and gif files to be used for rendering.
// In addition you can upload your own image. The image loading is provided by stb_image.
// The parameter imageFlags is combination of flags defined in NVGimageFlags.

// Creates image by loading it from the disk from specified file name.
// Returns handle to the image.
VG_API	int nvgCreateImage(vg_t* ctx, const char* filename, int imageFlags);

// Creates image by loading it from the specified chunk of memory.
// Returns handle to the image.
VG_API	int nvgCreateImageMem(vg_t* ctx, int imageFlags, unsigned char* data, int ndata);

// Creates image from specified image data.
// Returns handle to the image.
VG_API	int nvgCreateImageRGBA(vg_t* ctx, int w, int h, int imageFlags, const unsigned char* data);

// Updates image data specified by image handle.
VG_API	void nvgUpdateImage(vg_t* ctx, int image, const unsigned char* data);

// Returns the dimensions of a created image.
VG_API	void nvgImageSize(vg_t* ctx, int image, int* w, int* h);

VG_API	void vg_img_delete(vg_t* ctx, int* img);
VG_API	void vg_img_free(vg_t* ctx, int img);

//
// Paints
//
// NanoVG supports four types of paints: linear gradient, box gradient, radial gradient and image pattern.
// These can be used as paints for strokes and fills.

// Creates and returns a linear gradient. Parameters (sx,sy)-(ex,ey) specify the start and end coordinates
// of the linear gradient, icol specifies the start color and ocol the end color.
// The gradient is transformed by the current transform when it is passed to nvgFillPaint() or nvgStrokePaint().
VG_API	NVGpaint nvgLinearGradient(vg_t* ctx, float sx, float sy, float ex, float ey,
						   vg_color_t icol, vg_color_t ocol);

// Creates and returns a box gradient. Box gradient is a feathered rounded rectangle, it is useful for rendering
// drop shadows or highlights for boxes. Parameters (x,y) define the top-left corner of the rectangle,
// (w,h) define the size of the rectangle, r defines the corner radius, and f feather. Feather defines how blurry
// the border of the rectangle is. Parameter icol specifies the inner color and ocol the outer color of the gradient.
// The gradient is transformed by the current transform when it is passed to nvgFillPaint() or nvgStrokePaint().
VG_API	NVGpaint nvgBoxGradient(vg_t* ctx, float x, float y, float w, float h,
						float r, float f, vg_color_t icol, vg_color_t ocol);

// Creates and returns a radial gradient. Parameters (cx,cy) specify the center, inr and outr specify
// the inner and outer radius of the gradient, icol specifies the start color and ocol the end color.
// The gradient is transformed by the current transform when it is passed to nvgFillPaint() or nvgStrokePaint().
VG_API	NVGpaint nvgRadialGradient(vg_t* ctx, float cx, float cy, float inr, float outr,
						   vg_color_t icol, vg_color_t ocol);

// Creates and returns an image patter. Parameters (ox,oy) specify the left-top location of the image pattern,
// (ex,ey) the size of one image, angle rotation around the top-left corner, image is handle to the image to render.
// The gradient is transformed by the current transform when it is passed to nvgFillPaint() or nvgStrokePaint().
VG_API	NVGpaint nvgImagePattern(vg_t* ctx, float ox, float oy, float ex, float ey,
						 float angle, int image, float alpha);

//
// Scissoring
//
// Scissoring allows you to clip the rendering into a rectangle. This is useful for various
// user interface cases like rendering a text edit or a timeline.

// Sets current scissor rect. The scissor rect is transformed by current transform.
VG_API	void nvgScissor(vg_t* ctx, float x, float y, float w, float h);

// Intersects current scissor rectangle with the specified rectangle.
// The scissor rectangle is transformed by the current transform.
// Note: in case the rotation of previous scissor rect differs from
// the current one, the intersection will be done between the specified
// rectangle and the previous scissor rectangle transformed in the current
// transform space. The resulting shape is always rectangle.
VG_API	void nvgIntersectScissor(vg_t* ctx, float x, float y, float w, float h);

// Reset and disables scissoring.
VG_API	void nvgResetScissor(vg_t* ctx);

//
// Paths
//
// Drawing a new shape starts with nvgBeginPath(), it clears all the currently defined paths.
// Then you define one or more paths and sub-paths which describe the shape. The are functions
// to draw common shapes like rectangles and circles, and lower level step-by-step functions,
// which allow to define a path curve by curve.
//
// NanoVG uses even-odd fill rule to draw the shapes. Solid shapes should have counter clockwise
// winding and holes should have counter clockwise order. To specify winding of a path you can
// call nvgPathWinding(). This is useful especially for the common shapes, which are drawn CCW.
//
// Finally you can fill the path using current fill style by calling nvgFill(), and stroke it
// with current stroke style by calling nvgStroke().
//
// The curve segments and sub-paths are transformed by the current transform.
//
// SVG path commands: https://www.w3.org/TR/SVG/paths.html#PathDataLinetoCommands

// Clears the current path and sub-paths.
VG_API	void nvgBeginPath(vg_t* ctx);

// Starts new sub-path with specified point as first point.
VG_API	void nvgMoveTo(vg_t* ctx, float x, float y);

// Adds line segment from the last point in the path to the specified point.
VG_API	void nvgLineTo(vg_t* ctx, float x, float y);

// Adds cubic bezier segment from last point in the path via two control points to the specified point.
VG_API	void nvgBezierTo(vg_t* ctx, float c1x, float c1y, float c2x, float c2y, float x, float y);

// Adds quadratic bezier segment from last point in the path via a control point to the specified point.
VG_API	void nvgQuadTo(vg_t* ctx, float cx, float cy, float x, float y);

// Adds an arc segment at the corner defined by the last path point, and two specified points.
VG_API	void nvgArcTo(vg_t* ctx, float x1, float y1, float x2, float y2, float radius);

// Closes current sub-path with a line segment.
VG_API	void nvgClosePath(vg_t* ctx);

// Sets the current sub-path winding, see NVGwinding and NVGsolidity.
VG_API	void nvgPathWinding(vg_t* ctx, int dir);

// Creates new circle arc shaped sub-path. The arc center is at cx,cy, the arc radius is r,
// and the arc is drawn from angle a0 to a1, and swept in direction dir (NVG_CCW, or NVG_CW).
// Angles are specified in radians.
VG_API	void nvgArc(vg_t* ctx, float cx, float cy, float r, float a0, float a1, int dir);

// Creates new rectangle shaped sub-path.
VG_API	void nvgRect(vg_t* ctx, float x, float y, float w, float h);

// Creates new rounded rectangle shaped sub-path.
VG_API	void nvgRoundedRect(vg_t* ctx, float x, float y, float w, float h, float r);

// Creates new rounded rectangle shaped sub-path with varying radii for each corner.
VG_API	void nvgRoundedRectVarying(vg_t* ctx, float x, float y, float w, float h, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft);

// Creates new ellipse shaped sub-path.
VG_API	void nvgEllipse(vg_t* ctx, float cx, float cy, float rx, float ry);

// Creates new circle shaped sub-path.
VG_API	void nvgCircle(vg_t* ctx, float cx, float cy, float r);

// Fills the current path with current fill style.
VG_API	void nvgFill(vg_t* ctx);

// Fills the current path with current stroke style.
VG_API	void nvgStroke(vg_t* ctx);


//
// Text
//
// NanoVG allows you to load .ttf files and use the font to render text.
//
// The appearance of the text can be defined by setting the current text style
// and by specifying the fill color. Common text and font settings such as
// font size, letter spacing and text align are supported. Font blur allows you
// to create simple text effects such as drop shadows.
//
// At render time the font face can be set based on the font handles or name.
//
// Font measure functions return values in local space, the calculations are
// carried in the same resolution as the final rendering. This is done because
// the text glyph positions are snapped to the nearest pixels sharp rendering.
//
// The local space means that values are not rotated or scale as per the current
// transformation. For example if you set font size to 12, which would mean that
// line height is 16, then regardless of the current scaling and rotation, the
// returned line height is always 16. Some measures may vary because of the scaling
// since aforementioned pixel snapping.
//
// While this may sound a little odd, the setup allows you to always render the
// same way regardless of scaling. I.e. following works regardless of scaling:
//
//		const char* txt = "Text me up.";
//		nvgTextBounds(vg, x,y, txt, NULL, bounds);
//		nvgBeginPath(vg);
//		nvgRoundedRect(vg, bounds[0],bounds[1], bounds[2]-bounds[0], bounds[3]-bounds[1]);
//		nvgFill(vg);
//
// Note: currently only solid color fill is supported for text.


// Creates font by loading it from the disk from specified file name.
// Returns handle to the font.
VG_API	int nvgCreateFont(vg_t* ctx, const char* name, const char* filename);

// fontIndex specifies which font face to load from a .ttf/.ttc file.
VG_API	int nvgCreateFontAtIndex(vg_t* ctx, const char* name, const char* filename, const int fontIndex);

// Creates font by loading it from the specified memory chunk.
// Returns handle to the font.
VG_API	int nvgCreateFontMem(vg_t* ctx, const char* name, unsigned char* data, int ndata, int freeData);

// fontIndex specifies which font face to load from a .ttf/.ttc file.
VG_API	int nvgCreateFontMemAtIndex(vg_t* ctx, const char* name, unsigned char* data, int ndata, int freeData, const int fontIndex);

// Finds a loaded font of specified name, and returns handle to it, or -1 if the font is not found.
VG_API	int nvgFindFont(vg_t* ctx, const char* name);

// Adds a fallback font by handle/name.
VG_API	int nvgAddFallbackFontId(vg_t* ctx, int baseFont, int fallbackFont);
VG_API	int nvgAddFallbackFont(vg_t* ctx, const char* baseFont, const char* fallbackFont);

// Resets fallback fonts by handle/name
VG_API	void nvgResetFallbackFontsId(vg_t* ctx, int baseFont); // by handle.
VG_API	void nvgResetFallbackFonts(vg_t* ctx, const char* baseFont); // by name.

// Sets the font size of current text style.
VG_API	void nvgFontSize(vg_t* ctx, float size);

// Sets the blur of current text style.
VG_API	void nvgFontBlur(vg_t* ctx, float blur);

// Sets the font face based on specified id of current text style.
VG_API	void nvgFontFaceId(vg_t* ctx, int font);

// Sets the font face based on specified name of current text style.
VG_API	void nvgFontFace(vg_t* ctx, const char* font);

// Sets the letter spacing of current text style.
VG_API	void nvgTextLetterSpacing(vg_t* ctx, float spacing);

// Sets the proportional line height of current text style. The line height is specified as multiple of font size.
VG_API	void 	nvgTextLineHeight(vg_t* ctx, float lineHeight);

// Sets the text align of current text style, see NVGalign for options.
VG_API	void nvgTextAlign(vg_t* ctx, int align);

// Draws text string at specified location. If end is specified only the sub-string up to the end is drawn.
VG_API	float nvgText(vg_t* ctx, float x, float y, const char* string, const char* end);

// Draws multi-line text string at specified location wrapped at the specified width. If end is specified only the sub-string up to the end is drawn.
// White space is stripped at the beginning of the rows, the text is split at word boundaries or when new-line characters are encountered.
// Words longer than the max width are slit at nearest character (i.e. no hyphenation).
VG_API	void nvgTextBox(vg_t* ctx, float x, float y, float breakRowWidth, const char* string, const char* end);

// Measures the specified text string. Parameter bounds should be a pointer to float[4],
// if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
// Returns the horizontal advance of the measured text (i.e. where the next character should drawn).
// Measured values are returned in local coordinate space.
VG_API	float nvgTextBounds(vg_t* ctx, float x, float y, const char* string, const char* end, float* bounds);

// Measures the specified multi-text string. Parameter bounds should be a pointer to float[4],
// if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
// Measured values are returned in local coordinate space.
VG_API	void nvgTextBoxBounds(vg_t* ctx, float x, float y, float breakRowWidth, const char* string, const char* end, float* bounds);

// Calculates the glyph x positions of the specified text. If end is specified only the sub-string will be used.
// Measured values are returned in local coordinate space.
VG_API	int nvgTextGlyphPositions(vg_t* ctx, float x, float y, const char* string, const char* end, NVGglyphPosition* positions, int maxPositions);

// Returns the vertical metrics based on the current text style.
// Measured values are returned in local coordinate space.
VG_API	void nvgTextMetrics(vg_t* ctx, float* ascender, float* descender, float* lineh);

// Breaks the specified text into lines. If end is specified only the sub-string will be used.
// White space is stripped at the beginning of the rows, the text is split at word boundaries or when new-line characters are encountered.
// Words longer than the max width are slit at nearest character (i.e. no hyphenation).
VG_API	int nvgTextBreakLines(vg_t* ctx, const char* string, const char* end, float breakRowWidth, NVGtextRow* rows, int maxRows);

//
// Internal Render API
//
enum NVGtexture {
	NVG_TEXTURE_ALPHA = 0x01,
	NVG_TEXTURE_RGBA = 0x02,
};

struct NVGscissor {
	float xform[6];
	float extent[2];
};
typedef struct NVGscissor NVGscissor;

struct NVGvertex {
	float x,y,u,v;
};
typedef struct NVGvertex NVGvertex;

struct NVGpath {
	int first;
	int count;
	unsigned char closed;
	int nbevel;
	NVGvertex* fill;
	int nfill;
	NVGvertex* stroke;
	int nstroke;
	int winding;
	int convex;
};
typedef struct NVGpath NVGpath;

struct NVGparams {
	void* userPtr;
	int edgeAntiAlias;
	int (*renderCreate)(void* uptr);
	int (*renderCreateTexture)(void* uptr, int type, int w, int h, int imageFlags, const unsigned char* data);
	int (*renderDeleteTexture)(void* uptr, int image);
	int (*renderUpdateTexture)(void* uptr, int image, int x, int y, int w, int h, const unsigned char* data);
	int (*renderGetTextureSize)(void* uptr, int image, int* w, int* h);
	void (*renderViewport)(void* uptr, float width, float height, float devicePixelRatio);
	void (*renderCancel)(void* uptr);
	void (*renderFlush)(void* uptr);
	void (*renderFill)(void* uptr, NVGpaint* paint, NVGcompositeOperationState compositeOperation, NVGscissor* scissor, float fringe, const float* bounds, const NVGpath* paths, int npaths);
	void (*renderStroke)(void* uptr, NVGpaint* paint, NVGcompositeOperationState compositeOperation, NVGscissor* scissor, float fringe, float strokeWidth, const NVGpath* paths, int npaths);
	void (*renderTriangles)(void* uptr, NVGpaint* paint, NVGcompositeOperationState compositeOperation, NVGscissor* scissor, const NVGvertex* verts, int nverts, float fringe);
	void (*renderDelete)(void* uptr);
};
typedef struct NVGparams NVGparams;

// Constructor and destructor, called by the render back-end.
vg_t* nvgCreateInternal(NVGparams* params);
void nvgDeleteInternal(vg_t* ctx);

NVGparams* nvgInternalParams(vg_t* ctx);

// Debug function to dump cached path data.
void nvgDebugDumpPathCache(vg_t* ctx);

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#define NVG_NOTUSED(v) for (;;) { (void)(1 ? (void)0 : ( (void)(v) ) ); break; }

#ifdef __cplusplus
}
#endif

#endif // NANOVG_H
