@echo off
SET EPE=..\EnumParser\Debug\EnumParser.exe
SET TP=parserTemplates
SET SP=src\cards\types
SET GP=src\cards\types\generated
ECHO // generated include files > %GP%\generated.h 
SET ENUM=ArtifactType
%EPE% %SP%\%ENUM%.h %TP%\include.tpl +%GP%\generated.h %TP%\enum_include.tpl %GP%\%ENUM%Str.h %TP%\enum.tpl %GP%\%ENUM%Str.cpp
SET ENUM=CardType
%EPE% %SP%\%ENUM%.h %TP%\include.tpl +%GP%\generated.h %TP%\enum_include.tpl %GP%\%ENUM%Str.h %TP%\bitenum.tpl %GP%\%ENUM%Str.cpp
SET ENUM=CreatureType
%EPE% %SP%\%ENUM%.h %TP%\include.tpl +%GP%\generated.h %TP%\enum_include.tpl %GP%\%ENUM%Str.h %TP%\enum.tpl %GP%\%ENUM%Str.cpp
SET ENUM=EnchantmentType
%EPE% %SP%\%ENUM%.h %TP%\include.tpl +%GP%\generated.h %TP%\enum_include.tpl %GP%\%ENUM%Str.h %TP%\enum.tpl %GP%\%ENUM%Str.cpp
SET ENUM=LandType
%EPE% %SP%\%ENUM%.h %TP%\include.tpl +%GP%\generated.h %TP%\enum_include.tpl %GP%\%ENUM%Str.h %TP%\enum.tpl %GP%\%ENUM%Str.cpp
SET ENUM=PlaneswalkerType
%EPE% %SP%\%ENUM%.h %TP%\include.tpl +%GP%\generated.h %TP%\enum_include.tpl %GP%\%ENUM%Str.h %TP%\enum.tpl %GP%\%ENUM%Str.cpp
SET ENUM=Rarity
%EPE% %SP%\%ENUM%.h %TP%\include.tpl +%GP%\generated.h %TP%\enum_include.tpl %GP%\%ENUM%Str.h %TP%\enum.tpl %GP%\%ENUM%Str.cpp
SET ENUM=SpellType
%EPE% %SP%\%ENUM%.h %TP%\include.tpl +%GP%\generated.h %TP%\enum_include.tpl %GP%\%ENUM%Str.h %TP%\enum.tpl %GP%\%ENUM%Str.cpp
SET ENUM=SuperType
%EPE% %SP%\%ENUM%.h %TP%\include.tpl +%GP%\generated.h %TP%\enum_include.tpl %GP%\%ENUM%Str.h %TP%\bitenum.tpl %GP%\%ENUM%Str.cpp
