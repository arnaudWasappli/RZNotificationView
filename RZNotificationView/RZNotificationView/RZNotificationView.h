//
//  RZNotificationView.h
//  RZNotificationView
//
//  Created by Jérémy Lagrue on 25/09/12.
//  Copyright (c) 2012 Rezzza. All rights reserved.
//

@import UIKit;
@import AudioToolbox;

#import "RZNotificationLabelProtocol.h"
#import "UIViewController+RZTopMostController.h"

/**
 @enum RZNotificationIcon
 The icon to display
 */
typedef NS_ENUM(NSUInteger, RZNotificationIcon) {
    /** Facebook icon*/
    RZNotificationIconFacebook = 0,
    /** Gift icon*/
    RZNotificationIconGift,
    /** Info icon*/
    RZNotificationIconInfo,
    /** Smiley icon*/
    RZNotificationIconSmiley,
    /** Twitter icon*/
	RZNotificationIconTwitter,
    /** Warning icon*/
    RZNotificationIconWarning,
    /** Custom icon*/
    RZNotificationIconCustom,
    /** No icon*/
    RZNotificationIconNone
};

typedef NS_ENUM(NSUInteger, RZNotificationAnchor) {
    /** Arrow anchor*/
    RZNotificationAnchorArrow = 0,
    /** Close anchor*/
    RZNotificationAnchorX,
    /** No anchor*/
    RZNotificationAnchorNone
};

/**
 @enum RZNotificationPosition
 The positon of the notification view
 */
typedef NS_ENUM(NSUInteger, RZNotificationPosition) {
    /** The notification is displayed on top */
    RZNotificationPositionTop = 0,
    /** The notification is displayed on bottom */
    RZNotificationPositionBottom
};

/**
 @enum RZNotificationColor
 The color of the notification view
 */
typedef NS_ENUM(NSInteger, RZNotificationColor) {
    /** Yellow color*/
    RZNotificationColorYellow = 0,
    /** Red color*/
    RZNotificationColorRed,
    /** Light blue color*/
    RZNotificationColorLightBlue,
    /** Dark blue color*/
    RZNotificationColorDarkBlue,
    /** Purple color*/
    RZNotificationColorPurple,
    /** Orange color*/
    RZNotificationColorOrange,
    // Deprecations
    /** Grey color*/
    RZNotificationColorGrey __attribute__((deprecated)),
    /** Blue color*/
    RZNotificationColorBlue __attribute__((deprecated)) = RZNotificationColorLightBlue,
};

/**
 @enum RZNotificationContentColor
 The color of the notification view content
 */
typedef NS_ENUM(NSUInteger, RZNotificationContentColor) {
    /** Text is white */
    RZNotificationContentColorLight = 0,
    /** Text is grey */
    RZNotificationContentColorDark,
    /** Text color is set with textColor*/
    RZNotificationContentColorManual,
    /** Text is automatically lighter */
    RZNotificationContentColorAutomaticLight __attribute__((deprecated)),
    /** Text is automatically darker */
    RZNotificationContentColorAutomaticDark __attribute__((deprecated)),
};

/**
 @enum RZNotificationContext
 The context for displaying the notification
 */
typedef NS_ENUM(NSUInteger, RZNotificationContext) {
    /** Will take the controller displayed automatically */
    RZNotificationContextTopMostController,
    /** Will place the notification under the status bar */
    RZNotificationContextBelowStatusBar,
    /** Will place the notification above the status bar */
    RZNotificationContextAboveStatusBar
};

@class RZNotificationView;

typedef void (^RZNotificationCompletion)(BOOL touched);

@protocol RZNotificationViewProtocol

@optional
- (CGFloat)yOriginForRZNotificationViewForPosition:(RZNotificationPosition)position;
- (void)addRZNotificationView:(RZNotificationView*)view;

@end

/** Display a Notification easily
 
 This view allow you to display in app notification with a few lines of code
 
 # Show a tweet
 
    [RZNotificationView showNotificationOn:RZNotificationContextTopMostController
                                   message:@"This is a twitter message!"
                                      icon:RZNotificationIconTwitter
                                    anchor:RZNotificationAnchorX
                                  position:RZNotificationPositionTop
                                     color:RZNotificationColorYellow
                                assetColor:RZNotificationContentColorLight
                                 textColor:RZNotificationContentColorDark
                            withCompletion:nil];
 
 # Show a warning with custom sound and vibration
 
    RZNotificationView *notif = [RZNotificationView showNotificationWithMessage:@"Warning, you did something wrong."
                                                                           icon:RZNotificationIconWarning
                                                                         anchor:RZNotificationAnchorX
                                                                       position:RZNotificationPositionTop
                                                                          color:RZNotificationColorRed
                                                                     assetColor:RZNotificationContentColorDark
                                                                      textColor:RZNotificationContentColorLight
                                                              addedToController:self
                                                                 withCompletion:nil];
    [notif setSound:@"DoorBell-SoundBible.com-1986366504.wav"];
    [notif setVibrate:YES];

 # Show a facebook invitation
 
    [RZNotificationView showNotificationWithMessage:@"Tell your friends that RZNotificationView is awesome."
                                               icon:RZNotificationIconFacebook
                                             anchor:RZNotificationAnchorArrow
                                           position:RZNotificationPositionBottom
                                              color:RZNotificationColorDarkBlue
                                         assetColor:RZNotificationContentColorDark
                                          textColor:RZNotificationContentColorLight
                                  addedToController:self
                                     withCompletion:^(BOOL touched) {
                                         if (touched) {
                                             NSURL *fbURL = [NSURL URLWithString:@"fb://"];
                                             if ([[UIApplication sharedApplication] canOpenURL:fbURL]) {
                                                 [[UIApplication sharedApplication] openURL:fbURL];
                                             }
                                             else
                                                 [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://www.facebook.com"]];
                                         }
                                     }];
 */
@interface RZNotificationView : UIControl
{
    UIImageView *_iconView;
    UIImageView *_anchorView;
    BOOL _isTouch;
    
    SystemSoundID _soundFileObject;
    
}

/**---------------------------------------------------------------------------------------
 * @name Showing methods
 *  ---------------------------------------------------------------------------------------
 */

/**
 Show a notification on a specific controller
 @param message The message
 @param icon The icon
 @param anchor The anchor
 @param position The position
 @param color The notification color
 @param assetColor The asset color
 @param textColor The text color
 @param controller The specific controller that display the notification
 @param completionBlock The completionBlock to execute
 @return RZNotificationView intialized by given parameters
 */
+ (RZNotificationView*) showNotificationWithMessage:(NSString*)message icon:(RZNotificationIcon)icon anchor:(RZNotificationAnchor)anchor position:(RZNotificationPosition)position color:(RZNotificationColor)color assetColor:(RZNotificationContentColor)assetColor textColor:(RZNotificationContentColor)textColor addedToController:(UIViewController*)controller withCompletion:(RZNotificationCompletion)completionBlock;

/**
 Show a notification on a specific controller with delay
 @param message The message
 @param icon The icon
 @param anchor The anchor
 @param position The position
 @param color The notification color
 @param assetColor The asset color
 @param textColor The text color
 @param duration The delay before hiding the notification view
 @param controller The specific controller that display the notification
 @param completionBlock The completionBlock to execute
 @return RZNotificationView intialized by given parameters
 */
+ (RZNotificationView*) showNotificationWithMessage:(NSString*)message icon:(RZNotificationIcon)icon anchor:(RZNotificationAnchor)anchor position:(RZNotificationPosition)position color:(RZNotificationColor)color assetColor:(RZNotificationContentColor)assetColor textColor:(RZNotificationContentColor)textColor duration:(NSTimeInterval)duration addedToController:(UIViewController*)controller withCompletion:(RZNotificationCompletion)completionBlock;

/**
 Show a notification on top most controller (the controller currently displayed)
 @param context The context for presenting the notification
 @param message The message
 @param icon The icon
 @param anchor The anchor
 @param position The position
 @param color The notification color
 @param assetColor The asset color
 @param textColor The text color
 @param completionBlock The completionBlock to execute
 @return RZNotificationView intialized by given parameters
 */
+ (RZNotificationView*) showNotificationOn:(RZNotificationContext)context message:(NSString*)message icon:(RZNotificationIcon)icon anchor:(RZNotificationAnchor)anchor position:(RZNotificationPosition)position color:(RZNotificationColor)color assetColor:(RZNotificationContentColor)assetColor textColor:(RZNotificationContentColor)textColor withCompletion:(RZNotificationCompletion)completionBlock;

/**
 Show a notification on top most controller (the controller currently displayed)
 @param context The context for presenting the notification
 @param message The message
 @param icon The icon
 @param anchor The anchor
 @param position The position
 @param color The notification color
 @param assetColor The asset color
 @param textColor The text color
 @param duration The delay before hiding the notification view
 @param completionBlock The completionBlock to execute
 @return RZNotificationView intialized by given parameters
 */
+ (RZNotificationView*) showNotificationOn:(RZNotificationContext)context message:(NSString*)message icon:(RZNotificationIcon)icon anchor:(RZNotificationAnchor)anchor position:(RZNotificationPosition)position color:(RZNotificationColor)color assetColor:(RZNotificationContentColor)assetColor textColor:(RZNotificationContentColor)textColor duration:(NSTimeInterval)duration withCompletion:(RZNotificationCompletion)completionBlock;

/**---------------------------------------------------------------------------------------
 * @name Showing methods
 *  ---------------------------------------------------------------------------------------
 */

/**
 Hide notification view for a specific controller
 If the context is not top most, then it will automatically take the top most controller
 
 @param controller The controller expected to display a notification
 @return YES if a notification has been hidden, NO if there wasn't any notification view on controller
 */
+ (BOOL) hideLastNotificationForController:(UIViewController*)controller;

/**
 Hide all notifications view for a specific controller
 @param controller The controller expected to display a notification
 @return noumber of notifications hidden
 */
+ (NSUInteger) hideAllNotificationsForController:(UIViewController*)controller;

/**---------------------------------------------------------------------------------------
 * @name Init methods
 *  ---------------------------------------------------------------------------------------
 */

/**
 Init an empty notification view
 @param controller The controller expected to display a notification
 */
- (id) initWithController:(UIViewController*)controller;

/**
 Init a notification view for a specific controller without displaying it
 You should use this method when you want to use a customView instead of the textLabel
 @param controller The controller expected to display a notification
 @param icon The icon
 @param anchor The anchor
 @param position The position
 @param color The notification color
 @param assetColor The asset color
 @param textColor The text color
 @param delay The delay before hiding the notification view
 @param completionBlock The completionBlock to execute
 return the notification view initialized
 */
- (id) initWithController:(UIViewController*)controller icon:(RZNotificationIcon)icon anchor:(RZNotificationAnchor)anchor position:(RZNotificationPosition)position color:(RZNotificationColor)color assetColor:(RZNotificationContentColor)assetColor textColor:(RZNotificationContentColor)textColor duration:(NSTimeInterval)delay completion:(RZNotificationCompletion)completionBlock;

/**
 Init a notification view for a specific context without displaying it
 You should use this method when you want to use a customView instead of the textLabel
 @param context The context to display a notification
 @param icon The icon
 @param anchor The anchor
 @param position The position
 @param color The notification color
 @param assetColor The asset color
 @param textColor The text color
 @param delay The delay before hiding the notification view
 @param completionBlock The completionBlock to execute
 return the notification view initialized
 */
- (id) initWithContext:(RZNotificationContext)context icon:(RZNotificationIcon)icon anchor:(RZNotificationAnchor)anchor position:(RZNotificationPosition)position color:(RZNotificationColor)color assetColor:(RZNotificationContentColor)assetColor textColor:(RZNotificationContentColor)textColor duration:(NSTimeInterval)delay completion:(RZNotificationCompletion)completionBlock;

/**---------------------------------------------------------------------------------------
 * @name Other methods
 *  ---------------------------------------------------------------------------------------
 */

/**
 Allow to show the notification
 */
- (void) show;

/**
 Allow to hide the notification
 */
- (void) hide;

/**
 Allow to hide the notification after a delay
 @param delay delay in seconds
 */
- (void) hideAfterDelay:(NSTimeInterval)delay;

/**
 get the notificationView displayed on a specific controller
 @param controller The controller expected to display a notification
 */
+ (RZNotificationView*) notificationForController:(UIViewController*)controller;

/**
 get the all notificationViews displayed on a specific controller
 @param controller The controller expected to display a notification
 */
+ (NSArray*) allNotificationsForController:(UIViewController*)controller;

/**---------------------------------------------------------------------------------------
 * @name Default configurations. Note that it won't redraw the current displayed notifications
 *  ---------------------------------------------------------------------------------------
 */

/**
 *  Register the minimum height for the notifications
 *  Default is 54.0f
 *
 *  @param minimumHeight the min height
 */
+ (void) registerMinimumHeight:(CGFloat)minimumHeight;

/**
 *   Adjust margin on top and botton of textLabel or customView. (16px by default)
 *
 *  @param contentMarginHeight the margin
 */
+ (void) registerContentMarginOnHeight:(CGFloat)contentMarginHeight;

/**
 *  Register the x offset from border. Default is 16px
 *
 *  @param defaultXOffset the default x offset
 */
+ (void) registerDefaultOffsetOnX:(CGFloat)defaultXOffset;

/**---------------------------------------------------------------------------------------
 * @name Properties
 *  ---------------------------------------------------------------------------------------
 */

/**
 Getter for the textLabel
 This label display the message in case you don't use a customView
 */
@property (nonatomic, readonly) UILabel *textLabel;

/**
 Your customView
 - You can set your own view instead of a classic label
 - Your view has to coform to 
 - Have a look on samples
 */
@property (nonatomic, strong) id <RZNotificationLabelProtocol> customView;

/**
 Message to display in cas you use textLabel
 */
@property (nonatomic, strong) NSString *message;

/**
 Delay in seconds before hiding a notification view.
 It won't be hiddend if delay is Equal 0
 */
@property (nonatomic) NSTimeInterval delay;

/**
 Position of notification view
 */
@property (nonatomic) RZNotificationPosition position;

/**
 Background color of notification view if customTopColor and customBottomColor are not used
 */
@property (nonatomic) RZNotificationColor color;

/**
 Top color for background gradient color
 */
@property (nonatomic, strong) UIColor *customTopColor;

/**
 Botton color for background gradient color
 */
@property (nonatomic, strong) UIColor *customBottomColor;

/**
 Sound file name
 */
@property (nonatomic, strong) NSString *sound;

/**
 Activate or not the vibration
 */
@property (nonatomic) BOOL vibrate;

/**
 Color for icon background 
 */
@property (nonatomic) RZNotificationContentColor assetColor;

/**
 Text color
 */
@property (nonatomic) RZNotificationContentColor textColor;

/**
 Icon to display
 */
@property (nonatomic) RZNotificationIcon icon;

/**
 Anchor to display
 */
@property (nonatomic) RZNotificationAnchor anchor;


/**
 Icon filename for custom image
 */
@property (nonatomic, strong) NSString *customIcon;

/**
 Set the message lenght max you want to display. 3 char "..." will be added. Defaut value is 150
 */
@property (nonatomic) NSInteger messageMaxLenght;

/**
 *  Label font when using text. Default is avenir of 15px
 */
@property (nonatomic, strong) UIFont *labelFont UI_APPEARANCE_SELECTOR;

/**
 completionBlock to execute before hiding. Ability to kwon if notification view as been touched or not
 */
@property (nonatomic, strong) RZNotificationCompletion completionBlock;

#pragma mark - Deprecated

/**
 Adjust margin on top and botton of textLabel or customView. (16px by default)
 */
@property (nonatomic) CGFloat contentMarginHeight DEPRECATED_MSG_ATTRIBUTE("use `+registerContentMarginOnHeight:` instead");

/**
 Display or not the anchor (right image)
 */
@property (nonatomic) BOOL displayAnchor DEPRECATED_MSG_ATTRIBUTE("use `RZNotificationAnchor` or 'anchor' instead");

+ (RZNotificationView*) showNotificationWithMessage:(NSString*)message icon:(RZNotificationIcon)icon position:(RZNotificationPosition)position color:(RZNotificationColor)color assetColor:(RZNotificationContentColor)assetColor textColor:(RZNotificationContentColor)textColor addedToController:(UIViewController*)controller withCompletion:(RZNotificationCompletion)completionBlock DEPRECATED_ATTRIBUTE;
+ (RZNotificationView*) showNotificationWithMessage:(NSString*)message icon:(RZNotificationIcon)icon position:(RZNotificationPosition)position color:(RZNotificationColor)color assetColor:(RZNotificationContentColor)assetColor textColor:(RZNotificationContentColor)textColor delay:(NSTimeInterval)delay addedToController:(UIViewController*)controller withCompletion:(RZNotificationCompletion)completionBlock DEPRECATED_ATTRIBUTE;
+ (RZNotificationView*) showNotificationOnTopMostControllerWithMessage:(NSString*)message icon:(RZNotificationIcon)icon position:(RZNotificationPosition)position color:(RZNotificationColor)color assetColor:(RZNotificationContentColor)assetColor textColor:(RZNotificationContentColor)textColor withCompletion:(RZNotificationCompletion)completionBlock DEPRECATED_ATTRIBUTE;
+ (RZNotificationView*) showNotificationOnTopMostControllerWithMessage:(NSString*)message icon:(RZNotificationIcon)icon position:(RZNotificationPosition)position color:(RZNotificationColor)color assetColor:(RZNotificationContentColor)assetColor textColor:(RZNotificationContentColor)textColor delay:(NSTimeInterval)delay withCompletion:(RZNotificationCompletion)completionBlock DEPRECATED_ATTRIBUTE;
- (id) initWithController:(UIViewController*)controller icon:(RZNotificationIcon)icon position:(RZNotificationPosition)position color:(RZNotificationColor)color assetColor:(RZNotificationContentColor)assetColor textColor:(RZNotificationContentColor)textColor delay:(NSTimeInterval)delay completion:(RZNotificationCompletion)completionBlock DEPRECATED_ATTRIBUTE;

+ (BOOL) hideNotificationForController:(UIViewController*)controller DEPRECATED_MSG_ATTRIBUTE("use `hideLastNotificationForController` instead");

@end

#define RZSystemVersionGreaterOrEqualThan(version) ([[[UIDevice currentDevice] systemVersion] floatValue] >= version)
