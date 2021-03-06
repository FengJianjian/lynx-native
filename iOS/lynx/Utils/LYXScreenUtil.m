// Copyright 2017 The Lynx Authors. All rights reserved.

#import "LYXScreenUtil.h"

@implementation LYXScreenUtil

static LYXScreenUtil *_singleLeton;

+ (instancetype) shareInstance {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _singleLeton = [[self alloc] init];
    });
    
    return _singleLeton;
}

- (instancetype) init {
    self = [super init];
    if (self) {
        // TODO: pt and px
        CGRect screenRect = [UIScreen mainScreen].bounds;
        _screenWidth = screenRect.size.width;
        _screenHeight = screenRect.size.height;
        _screenDensity = 1;
    }
    return self;
}

@end
