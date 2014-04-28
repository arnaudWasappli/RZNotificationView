//
//  SampleViewController.h
//  RZNotificationView
//
//  Created by Jérémy Lagrue on 25/09/12.
//  Copyright (c) 2012 Rezzza. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RZNotificationView.h"
#import <QuartzCore/QuartzCore.h>
#import "WEPopoverController.h"
#import "ColorViewController.h"

typedef enum {
    SampleMessageShort = 0,
    SampleMessageMedium,
    SampleMessageLong
}SampleMessage;

typedef enum
{
    RZSampleFormShowButton,
    RZSampleFormDelay,
    RZSampleFormTopBotColors,
    RZSampleFormPredefinedColors,
    RZSampleFormPosition,
    RZSampleFormVibrate,
    RZSampleFormHideShowNavBar,
    RZSampleFormTextSample,
    RZSampleFormAssetColor,
    RZSampleFormTextColor,
    RZSampleFormContent,
    RZSampleFormSound,
    RZSampleFormAnchor,
    RZSampleFormMargin,
    RZSampleFormMaxLength
}RZSampleFormType;

@class PrettyGridTableViewCell;

@interface SampleViewController : UIViewController <UITableViewDataSource, UITableViewDelegate, WEPopoverControllerDelegate, UIPopoverControllerDelegate, ColorViewControllerDelegate>
{
    UISlider *_delaySlider;
    UILabel *_delayLabel;
    
    IBOutlet UITableView *_tableView;
    NSArray *_formArray;
    
    NSInteger _current;
    NSIndexPath *_indexPath;
    SampleMessage _sampleMessage;
    NSInteger _roundIndex;
    
    BOOL _vibrate;
    NSString *_sound;
    BOOL _anchor;
    
    UIColor *_customTopColor, *_customBottomColor;
    
    RZNotificationColor _color;
    RZNotificationPosition _position;
    RZNotificationContentColor _assetColor;
    RZNotificationContentColor _textColor;
    
    id<RZNotificationLabelProtocol> _customView;
    
    UISlider *_marginHeigtSlider;
    UILabel *_marginHeigtLabel;
    
    UISlider *_maxLenghtSlider;
    UILabel *_maxLenghtLabel;
}

@property (nonatomic, strong) WEPopoverController *popoverController;
@property (nonatomic, strong) IBOutlet UITableView *tableView;

- (IBAction) navBarHidden:(id)sender;
- (IBAction) sliderValueChanged:(id)sender;
- (void) switchChange:(UISwitch*)sender;

@end
