#undef ENUM_ITEM
#undef ENUM_ITEM_VALUE
#undef ENUM_ITEM_NAME
#undef ENUM_ITEM_NONAME

#undef BEGIN_ENUM
#undef END_ENUM
#undef NUMBER_OF
#undef INVALID_ENUM_ITEM

#ifndef ENUM_STRCMP
#define ENUM_STRCMP strcasecmp
#endif

#ifndef __ENUM_NAMES_TYPE__
#define __ENUM_NAMES_TYPE__
typedef struct { int value; const char *name; }  ENUM_NAME_MAP_T;
const char *GetNameByValue(ENUM_NAME_MAP_T mapEnumName[], int count, int value);
#endif // __ENUM_STR_TYPE__

#ifndef GENERATE_ENUM_NAMES

    #define ENUM_ITEM( element )              element ,
    #define ENUM_ITEM_VALUE( element, value ) element = value ,
    #define ENUM_ITEM_NAME( element, name )   element ,
    #define ENUM_ITEM_NONAME( element, name ) element ,

    #define BEGIN_ENUM( ENUM_NAME )           typedef enum etag##ENUM_NAME {
    #define END_ENUM( ENUM_NAME )             invalid##ENUM_NAME##EnumValue } ENUM_NAME; \
	const char* Get##ENUM_NAME##NameByValue ( ENUM_NAME value ); \
	ENUM_NAME Get##ENUM_NAME##ValueByName ( const char *name ); \
	int GetNumberOf##ENUM_NAME##Items ( void ); \
	ENUM_NAME Get##ENUM_NAME##ValueAt ( int index ); \
	const char * Get##ENUM_NAME##NameAt ( int index ); \
	int Get##ENUM_NAME##PositionByValue ( ENUM_NAME value );

	#define NUMBER_OF( ENUM_NAME )                 GetNumberOf##ENUM_NAME##Items()
	#define INVALID_ENUM_ITEM( ENUM_NAME )         invalid##ENUM_NAME##EnumValue

	#define ENUM_NAME_BY_VALUE( ENUM_NAME, value ) Get##ENUM_NAME##NameByValue(value)
	#define ENUM_NAME( ENUM_NAME, value )          ENUM_NAME_BY_VALUE( ENUM_NAME, value )
	#define ENUM_VALUE_BY_NAME( ENUM_NAME, name )  Get##ENUM_NAME##ValueByName(name)
	#define ENUM_VALUE( ENUM_NAME, name )          ENUM_VALUE_BY_NAME( ENUM_NAME, name )
	#define ENUM_NAME_AT( ENUM_NAME, index )       Get##ENUM_NAME##NameAt(index)
	#define ENUM_VALUE_AT( ENUM_NAME, index )      Get##ENUM_NAME##ValueAt(index)
	#define ENUM_POS_BY_VALUE( ENUM_NAME, value )  Get##ENUM_NAME##PositionByValue(value)
	#define ENUM_POS( ENUM_NAME, value )           ENUM_POS_BY_VALUE( ENUM_NAME, value )

#else

	#define ENUM_ITEM( element )               { element, #element } ,
	#define ENUM_ITEM_VALUE( element, value )  ENUM_ITEM( element )
    #define ENUM_ITEM_NAME( element, name )    { element, name } ,
    #define ENUM_ITEM_NONAME( element, name )  

	#define NUMBER_OF( ENUM_NAME )             ((int)(sizeof ( g_mev2n_##ENUM_NAME ) / sizeof ( g_mev2n_##ENUM_NAME[0] )) - 1)
	#define INVALID_ENUM_ITEM( ENUM_NAME )     invalid##ENUM_NAME##EnumValue

	#define BEGIN_ENUM( ENUM_NAME )            static ENUM_NAME_MAP_T g_mev2n_##ENUM_NAME [] = {
	#define END_ENUM( ENUM_NAME )              {invalid##ENUM_NAME##EnumValue, (0)} }; \
	const char* Get##ENUM_NAME##NameByValue ( ENUM_NAME value ) \
	{ \
		return GetNameByValue(g_mev2n_##ENUM_NAME, NUMBER_OF( ENUM_NAME ), value); \
	} \
	ENUM_NAME Get##ENUM_NAME##ValueByName ( const char * name ) \
	{ \
		int i; \
		for ( i = 0; i < NUMBER_OF( ENUM_NAME ) ; i++ ) \
		{ \
			if ( ENUM_STRCMP (name, g_mev2n_##ENUM_NAME [i].name) == 0 ) { \
				return (ENUM_NAME)(g_mev2n_##ENUM_NAME [i].value); \
			} \
		} \
		return invalid##ENUM_NAME##EnumValue; \
	} \
	ENUM_NAME Get##ENUM_NAME##ValueAt( int index ) \
	{ \
		if (index >= 0 && index < NUMBER_OF( ENUM_NAME )) {\
			return (ENUM_NAME)(g_mev2n_##ENUM_NAME [ index ].value); \
		} else {\
			return invalid##ENUM_NAME##EnumValue; \
		} \
	} \
	const char * Get##ENUM_NAME##NameAt ( int index ) \
	{ \
		if (index >= 0 && index < NUMBER_OF( ENUM_NAME )) {\
			return (g_mev2n_##ENUM_NAME [ index ].name); \
		} else { \
			return (0); \
		} \
	} \
	int GetNumberOf##ENUM_NAME##Items ( void ) { return NUMBER_OF( ENUM_NAME ); } \
	int Get##ENUM_NAME##PositionByValue ( ENUM_NAME value ) \
	{ \
		int i; \
		for ( i = 0; i < NUMBER_OF( ENUM_NAME ) ; i++ ) \
		{ \
			if ( g_mev2n_##ENUM_NAME [i].value == (int)value ) \
				return i; \
		} \
		return -1; \
	}

#endif // defined GENERATE_ENUM_NAMES
