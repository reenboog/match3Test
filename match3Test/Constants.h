//
//  Constants.h
//  match3Test
//
//  Created by Alex Gievsky on 19.06.13.
//  Copyright (c) 2013 reenboog. All rights reserved.
//

#ifndef match3Test_Constants_h
#define match3Test_Constants_h

#define kScreenWidth        755
#define kScreenHeight       600

#define kNumOfChipTypes     5
#define kFieldBasePoint     v2(320, 100)
#define kChipSpacing        10
#define kChipWidth          35
#define kChipHeight         35

#define kScorePerChip       10

#define kFieldWidth         8
#define kFieldHeight        8

#define kGameSessionTime    60

#define kFieldAreaWidth (kFieldWidth * kChipWidth + (kFieldWidth - 1) * kChipSpacing)
#define kFieldAreaHeight (kFieldHeight * kChipHeight + (kFieldHeight - 1) * kChipSpacing)

#endif
