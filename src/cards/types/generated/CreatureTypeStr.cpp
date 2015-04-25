#include "../TypeToStr.h"
#include <unordered_map>

namespace mtg {

CreatureType parseCreatureType(std::string const & value) {
	static std::unordered_map<std::string,CreatureType> map;
	if( map.empty() ) {
		map["Advisor"] = Advisor;
		map["Ally"] = Ally;
		map["Angel"] = Angel;
		map["Anteater"] = Anteater;
		map["Antelope"] = Antelope;
		map["Ape"] = Ape;
		map["Archer"] = Archer;
		map["Archon"] = Archon;
		map["Artificer"] = Artificer;
		map["Assassin"] = Assassin;
		map["Assembly_Worker"] = Assembly_Worker;
		map["Atog"] = Atog;
		map["Aurochs"] = Aurochs;
		map["Avatar"] = Avatar;
		map["Badger"] = Badger;
		map["Barbarian"] = Barbarian;
		map["Basilisk"] = Basilisk;
		map["Bat"] = Bat;
		map["Bear"] = Bear;
		map["Beast"] = Beast;
		map["Beeble"] = Beeble;
		map["Berserker"] = Berserker;
		map["Bird"] = Bird;
		map["Blinkmoth"] = Blinkmoth;
		map["Boar"] = Boar;
		map["Bringer"] = Bringer;
		map["Brushwagg"] = Brushwagg;
		map["Camarid"] = Camarid;
		map["Camel"] = Camel;
		map["Caribou"] = Caribou;
		map["Carrier"] = Carrier;
		map["Cat"] = Cat;
		map["Centaur"] = Centaur;
		map["Cephalid"] = Cephalid;
		map["Chimera"] = Chimera;
		map["Citizen"] = Citizen;
		map["Cleric"] = Cleric;
		map["Cockatrice"] = Cockatrice;
		map["Construct"] = Construct;
		map["Coward"] = Coward;
		map["Crab"] = Crab;
		map["Crocodile"] = Crocodile;
		map["Cyclops"] = Cyclops;
		map["Dauthi"] = Dauthi;
		map["Demon"] = Demon;
		map["Deserter"] = Deserter;
		map["Devil"] = Devil;
		map["Djinn"] = Djinn;
		map["Dragon"] = Dragon;
		map["Drake"] = Drake;
		map["Dreadnought"] = Dreadnought;
		map["Drone"] = Drone;
		map["Druid"] = Druid;
		map["Dryad"] = Dryad;
		map["Dwarf"] = Dwarf;
		map["Efreet"] = Efreet;
		map["Egg"] = Egg;
		map["Elder"] = Elder;
		map["Eldrazi"] = Eldrazi;
		map["Elemental"] = Elemental;
		map["Elephant"] = Elephant;
		map["Elf"] = Elf;
		map["Elk"] = Elk;
		map["Eye"] = Eye;
		map["Faerie"] = Faerie;
		map["Ferret"] = Ferret;
		map["Fish"] = Fish;
		map["Flagbearer"] = Flagbearer;
		map["Fox"] = Fox;
		map["Frog"] = Frog;
		map["Fungus"] = Fungus;
		map["Gargoyle"] = Gargoyle;
		map["Germ"] = Germ;
		map["Giant"] = Giant;
		map["Gnome"] = Gnome;
		map["Goat"] = Goat;
		map["Goblin"] = Goblin;
		map["Golem"] = Golem;
		map["Gorgon"] = Gorgon;
		map["Graveborn"] = Graveborn;
		map["Gremlin"] = Gremlin;
		map["Griffin"] = Griffin;
		map["Hag"] = Hag;
		map["Harpy"] = Harpy;
		map["Hellion"] = Hellion;
		map["Hippo"] = Hippo;
		map["Hippogriff"] = Hippogriff;
		map["Homarid"] = Homarid;
		map["Homunculus"] = Homunculus;
		map["Horror"] = Horror;
		map["Horse"] = Horse;
		map["Hound"] = Hound;
		map["Human"] = Human;
		map["Hydra"] = Hydra;
		map["Hyena"] = Hyena;
		map["Illusion"] = Illusion;
		map["Imp"] = Imp;
		map["Incarnation"] = Incarnation;
		map["Insect"] = Insect;
		map["Jellyfish"] = Jellyfish;
		map["Juggernaut"] = Juggernaut;
		map["Kavu"] = Kavu;
		map["Kirin"] = Kirin;
		map["Kithkin"] = Kithkin;
		map["Knight"] = Knight;
		map["Kobold"] = Kobold;
		map["Kor"] = Kor;
		map["Kraken"] = Kraken;
		map["Lammasu"] = Lammasu;
		map["Leech"] = Leech;
		map["Leviathan"] = Leviathan;
		map["Lhurgoyf"] = Lhurgoyf;
		map["Licid"] = Licid;
		map["Lizard"] = Lizard;
		map["Manticore"] = Manticore;
		map["Masticore"] = Masticore;
		map["Mercenary"] = Mercenary;
		map["Merfolk"] = Merfolk;
		map["Metathran"] = Metathran;
		map["Minion"] = Minion;
		map["Minotaur"] = Minotaur;
		map["Monger"] = Monger;
		map["Mongoose"] = Mongoose;
		map["Monk"] = Monk;
		map["Moonfolk"] = Moonfolk;
		map["Mutant"] = Mutant;
		map["Myr"] = Myr;
		map["Mystic"] = Mystic;
		map["Nautilus"] = Nautilus;
		map["Nephilim"] = Nephilim;
		map["Nightmare"] = Nightmare;
		map["Nightstalker"] = Nightstalker;
		map["Ninja"] = Ninja;
		map["Noggle"] = Noggle;
		map["Nomad"] = Nomad;
		map["Octopus"] = Octopus;
		map["Ogre"] = Ogre;
		map["Ooze"] = Ooze;
		map["Orb"] = Orb;
		map["Orc"] = Orc;
		map["Orgg"] = Orgg;
		map["Ouphe"] = Ouphe;
		map["Ox"] = Ox;
		map["Oyster"] = Oyster;
		map["Pegasus"] = Pegasus;
		map["Pentavite"] = Pentavite;
		map["Pest"] = Pest;
		map["Phelddagrif"] = Phelddagrif;
		map["Phoenix"] = Phoenix;
		map["Pincher"] = Pincher;
		map["Pirate"] = Pirate;
		map["Plant"] = Plant;
		map["Praetor"] = Praetor;
		map["Prism"] = Prism;
		map["Rabbit"] = Rabbit;
		map["Rat"] = Rat;
		map["Rebel"] = Rebel;
		map["Reflection"] = Reflection;
		map["Rhino"] = Rhino;
		map["Rigger"] = Rigger;
		map["Rogue"] = Rogue;
		map["Rukh"] = Rukh;
		map["Salamander"] = Salamander;
		map["Samurai"] = Samurai;
		map["Sand"] = Sand;
		map["Saproling"] = Saproling;
		map["Satyr"] = Satyr;
		map["Scarecrow"] = Scarecrow;
		map["Scorpion"] = Scorpion;
		map["Scout"] = Scout;
		map["Serf"] = Serf;
		map["Serpent"] = Serpent;
		map["Shade"] = Shade;
		map["Shaman"] = Shaman;
		map["Shapeshifter"] = Shapeshifter;
		map["Sheep"] = Sheep;
		map["Siren"] = Siren;
		map["Skeleton"] = Skeleton;
		map["Slith"] = Slith;
		map["Sliver"] = Sliver;
		map["Slug"] = Slug;
		map["Snake"] = Snake;
		map["Soldier"] = Soldier;
		map["Soltari"] = Soltari;
		map["Spawn"] = Spawn;
		map["Specter"] = Specter;
		map["Spellshaper"] = Spellshaper;
		map["Sphinx"] = Sphinx;
		map["Spider"] = Spider;
		map["Spike"] = Spike;
		map["Spirit"] = Spirit;
		map["Splinter"] = Splinter;
		map["Sponge"] = Sponge;
		map["Squid"] = Squid;
		map["Squirrel"] = Squirrel;
		map["Starfish"] = Starfish;
		map["Surrakar"] = Surrakar;
		map["Survivor"] = Survivor;
		map["Tetravite"] = Tetravite;
		map["Thalakos"] = Thalakos;
		map["Thopter"] = Thopter;
		map["Thrull"] = Thrull;
		map["Treefolk"] = Treefolk;
		map["Triskelavite"] = Triskelavite;
		map["Troll"] = Troll;
		map["Turtle"] = Turtle;
		map["Twin"] = Twin;
		map["Unicorn"] = Unicorn;
		map["Vampire"] = Vampire;
		map["Vedalken"] = Vedalken;
		map["Viashino"] = Viashino;
		map["Volver"] = Volver;
		map["Wall"] = Wall;
		map["Warrior"] = Warrior;
		map["Wasp"] = Wasp;
		map["Weird"] = Weird;
		map["Werewolf"] = Werewolf;
		map["Whale"] = Whale;
		map["Wizard"] = Wizard;
		map["Wolf"] = Wolf;
		map["Wolverine"] = Wolverine;
		map["Wombat"] = Wombat;
		map["Worm"] = Worm;
		map["Wraith"] = Wraith;
		map["Wurm"] = Wurm;
		map["Yeti"] = Yeti;
		map["Zombie"] = Zombie;
		map["Zubera"] = Zubera;
	}
	return map.at(value);
}

std::string CreatureTypeStr(CreatureType value) {
	switch(value) {
	case Advisor:
		return "Advisor";
	case Ally:
		return "Ally";
	case Angel:
		return "Angel";
	case Anteater:
		return "Anteater";
	case Antelope:
		return "Antelope";
	case Ape:
		return "Ape";
	case Archer:
		return "Archer";
	case Archon:
		return "Archon";
	case Artificer:
		return "Artificer";
	case Assassin:
		return "Assassin";
	case Assembly_Worker:
		return "Assembly_Worker";
	case Atog:
		return "Atog";
	case Aurochs:
		return "Aurochs";
	case Avatar:
		return "Avatar";
	case Badger:
		return "Badger";
	case Barbarian:
		return "Barbarian";
	case Basilisk:
		return "Basilisk";
	case Bat:
		return "Bat";
	case Bear:
		return "Bear";
	case Beast:
		return "Beast";
	case Beeble:
		return "Beeble";
	case Berserker:
		return "Berserker";
	case Bird:
		return "Bird";
	case Blinkmoth:
		return "Blinkmoth";
	case Boar:
		return "Boar";
	case Bringer:
		return "Bringer";
	case Brushwagg:
		return "Brushwagg";
	case Camarid:
		return "Camarid";
	case Camel:
		return "Camel";
	case Caribou:
		return "Caribou";
	case Carrier:
		return "Carrier";
	case Cat:
		return "Cat";
	case Centaur:
		return "Centaur";
	case Cephalid:
		return "Cephalid";
	case Chimera:
		return "Chimera";
	case Citizen:
		return "Citizen";
	case Cleric:
		return "Cleric";
	case Cockatrice:
		return "Cockatrice";
	case Construct:
		return "Construct";
	case Coward:
		return "Coward";
	case Crab:
		return "Crab";
	case Crocodile:
		return "Crocodile";
	case Cyclops:
		return "Cyclops";
	case Dauthi:
		return "Dauthi";
	case Demon:
		return "Demon";
	case Deserter:
		return "Deserter";
	case Devil:
		return "Devil";
	case Djinn:
		return "Djinn";
	case Dragon:
		return "Dragon";
	case Drake:
		return "Drake";
	case Dreadnought:
		return "Dreadnought";
	case Drone:
		return "Drone";
	case Druid:
		return "Druid";
	case Dryad:
		return "Dryad";
	case Dwarf:
		return "Dwarf";
	case Efreet:
		return "Efreet";
	case Egg:
		return "Egg";
	case Elder:
		return "Elder";
	case Eldrazi:
		return "Eldrazi";
	case Elemental:
		return "Elemental";
	case Elephant:
		return "Elephant";
	case Elf:
		return "Elf";
	case Elk:
		return "Elk";
	case Eye:
		return "Eye";
	case Faerie:
		return "Faerie";
	case Ferret:
		return "Ferret";
	case Fish:
		return "Fish";
	case Flagbearer:
		return "Flagbearer";
	case Fox:
		return "Fox";
	case Frog:
		return "Frog";
	case Fungus:
		return "Fungus";
	case Gargoyle:
		return "Gargoyle";
	case Germ:
		return "Germ";
	case Giant:
		return "Giant";
	case Gnome:
		return "Gnome";
	case Goat:
		return "Goat";
	case Goblin:
		return "Goblin";
	case Golem:
		return "Golem";
	case Gorgon:
		return "Gorgon";
	case Graveborn:
		return "Graveborn";
	case Gremlin:
		return "Gremlin";
	case Griffin:
		return "Griffin";
	case Hag:
		return "Hag";
	case Harpy:
		return "Harpy";
	case Hellion:
		return "Hellion";
	case Hippo:
		return "Hippo";
	case Hippogriff:
		return "Hippogriff";
	case Homarid:
		return "Homarid";
	case Homunculus:
		return "Homunculus";
	case Horror:
		return "Horror";
	case Horse:
		return "Horse";
	case Hound:
		return "Hound";
	case Human:
		return "Human";
	case Hydra:
		return "Hydra";
	case Hyena:
		return "Hyena";
	case Illusion:
		return "Illusion";
	case Imp:
		return "Imp";
	case Incarnation:
		return "Incarnation";
	case Insect:
		return "Insect";
	case Jellyfish:
		return "Jellyfish";
	case Juggernaut:
		return "Juggernaut";
	case Kavu:
		return "Kavu";
	case Kirin:
		return "Kirin";
	case Kithkin:
		return "Kithkin";
	case Knight:
		return "Knight";
	case Kobold:
		return "Kobold";
	case Kor:
		return "Kor";
	case Kraken:
		return "Kraken";
	case Lammasu:
		return "Lammasu";
	case Leech:
		return "Leech";
	case Leviathan:
		return "Leviathan";
	case Lhurgoyf:
		return "Lhurgoyf";
	case Licid:
		return "Licid";
	case Lizard:
		return "Lizard";
	case Manticore:
		return "Manticore";
	case Masticore:
		return "Masticore";
	case Mercenary:
		return "Mercenary";
	case Merfolk:
		return "Merfolk";
	case Metathran:
		return "Metathran";
	case Minion:
		return "Minion";
	case Minotaur:
		return "Minotaur";
	case Monger:
		return "Monger";
	case Mongoose:
		return "Mongoose";
	case Monk:
		return "Monk";
	case Moonfolk:
		return "Moonfolk";
	case Mutant:
		return "Mutant";
	case Myr:
		return "Myr";
	case Mystic:
		return "Mystic";
	case Nautilus:
		return "Nautilus";
	case Nephilim:
		return "Nephilim";
	case Nightmare:
		return "Nightmare";
	case Nightstalker:
		return "Nightstalker";
	case Ninja:
		return "Ninja";
	case Noggle:
		return "Noggle";
	case Nomad:
		return "Nomad";
	case Octopus:
		return "Octopus";
	case Ogre:
		return "Ogre";
	case Ooze:
		return "Ooze";
	case Orb:
		return "Orb";
	case Orc:
		return "Orc";
	case Orgg:
		return "Orgg";
	case Ouphe:
		return "Ouphe";
	case Ox:
		return "Ox";
	case Oyster:
		return "Oyster";
	case Pegasus:
		return "Pegasus";
	case Pentavite:
		return "Pentavite";
	case Pest:
		return "Pest";
	case Phelddagrif:
		return "Phelddagrif";
	case Phoenix:
		return "Phoenix";
	case Pincher:
		return "Pincher";
	case Pirate:
		return "Pirate";
	case Plant:
		return "Plant";
	case Praetor:
		return "Praetor";
	case Prism:
		return "Prism";
	case Rabbit:
		return "Rabbit";
	case Rat:
		return "Rat";
	case Rebel:
		return "Rebel";
	case Reflection:
		return "Reflection";
	case Rhino:
		return "Rhino";
	case Rigger:
		return "Rigger";
	case Rogue:
		return "Rogue";
	case Rukh:
		return "Rukh";
	case Salamander:
		return "Salamander";
	case Samurai:
		return "Samurai";
	case Sand:
		return "Sand";
	case Saproling:
		return "Saproling";
	case Satyr:
		return "Satyr";
	case Scarecrow:
		return "Scarecrow";
	case Scorpion:
		return "Scorpion";
	case Scout:
		return "Scout";
	case Serf:
		return "Serf";
	case Serpent:
		return "Serpent";
	case Shade:
		return "Shade";
	case Shaman:
		return "Shaman";
	case Shapeshifter:
		return "Shapeshifter";
	case Sheep:
		return "Sheep";
	case Siren:
		return "Siren";
	case Skeleton:
		return "Skeleton";
	case Slith:
		return "Slith";
	case Sliver:
		return "Sliver";
	case Slug:
		return "Slug";
	case Snake:
		return "Snake";
	case Soldier:
		return "Soldier";
	case Soltari:
		return "Soltari";
	case Spawn:
		return "Spawn";
	case Specter:
		return "Specter";
	case Spellshaper:
		return "Spellshaper";
	case Sphinx:
		return "Sphinx";
	case Spider:
		return "Spider";
	case Spike:
		return "Spike";
	case Spirit:
		return "Spirit";
	case Splinter:
		return "Splinter";
	case Sponge:
		return "Sponge";
	case Squid:
		return "Squid";
	case Squirrel:
		return "Squirrel";
	case Starfish:
		return "Starfish";
	case Surrakar:
		return "Surrakar";
	case Survivor:
		return "Survivor";
	case Tetravite:
		return "Tetravite";
	case Thalakos:
		return "Thalakos";
	case Thopter:
		return "Thopter";
	case Thrull:
		return "Thrull";
	case Treefolk:
		return "Treefolk";
	case Triskelavite:
		return "Triskelavite";
	case Troll:
		return "Troll";
	case Turtle:
		return "Turtle";
	case Twin:
		return "Twin";
	case Unicorn:
		return "Unicorn";
	case Vampire:
		return "Vampire";
	case Vedalken:
		return "Vedalken";
	case Viashino:
		return "Viashino";
	case Volver:
		return "Volver";
	case Wall:
		return "Wall";
	case Warrior:
		return "Warrior";
	case Wasp:
		return "Wasp";
	case Weird:
		return "Weird";
	case Werewolf:
		return "Werewolf";
	case Whale:
		return "Whale";
	case Wizard:
		return "Wizard";
	case Wolf:
		return "Wolf";
	case Wolverine:
		return "Wolverine";
	case Wombat:
		return "Wombat";
	case Worm:
		return "Worm";
	case Wraith:
		return "Wraith";
	case Wurm:
		return "Wurm";
	case Yeti:
		return "Yeti";
	case Zombie:
		return "Zombie";
	case Zubera:
		return "Zubera";
	default:
		return value == 0 ? "0" : "unknown";
	}
}

}
