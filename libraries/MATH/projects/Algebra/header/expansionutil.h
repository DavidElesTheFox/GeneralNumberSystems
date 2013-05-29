#ifndef MATH__ALGEBRA__EXPANSIONUTIL_H
#define MATH__ALGEBRA__EXPANSIONUTIL_H

/** 
  * @file expansionutil.h
  * @brief This class contains some usefull macros new field generation
  */

#include "polynomial.h"
#include "fieldexpansion.h"
#include "idealadicrepresentation.h"
#include "number_traits.h"
#include "numbercalculator.h"

#include <vector>

/**
  * @brief Simple algebrical Extension
  * @details This macro creates a new algebrical type
  * @param BASE_FIELD The type of the base field
  * @param MINIMAL_POLYNOM The minimal Polynomial object
  * @param NAME the name of the new type
  * @param NAME_STR the string shape of the new algebrical element
  */
#define ALGEBRICAL_EXPANSION(BASE_FIELD, MINIMAL_POLYNOM, NAME, NAME_STR) \
  ALGEBRICAL_EXPANSION_LONG(BASE_FIELD, MINIMAL_POLYNOM, NAME, NAME_STR, MATH::Algebra::Number_traits<BASE_FIELD>, std::vector<BASE_FIELD>)

/*****************************************************************************/
/**
  * @brief Simple non algebrical Extension
  * @details This macro creates a new algebrical type
  * @param BASE_FIELD The type of the base field
  * @param NAME the name of the new type
  * @param NAME_STR the string shape of the new algebrical element
  */
#define NON_ALGEBRICAL_EXPANSION(BASE_FIELD, NAME, NAME_STR) \
  NON_ALGEBRICAL_EXPANSION_LONG(BASE_FIELD, NAME, NAME_STR, MATH::Algebra::Number_traits<BASE_FIELD>, std::vector<BASE_FIELD>)

/*****************************************************************************/
/**
  * @brief Simple non algebrical Extension, with long format
  * @details This macro creates a new algebrical type. You can determine
  *          the used traits class and container
  * @param BASE_FIELD The type of the base field
  * @param NAME the name of the new type
  * @param NAME_STR the string shape of the new algebrical element
  * @param NUMBER_TRAITS The traits class for BASE_FIELD
  * @param CONTAINER The type of the used container
  */
#define NON_ALGEBRICAL_EXPANSION_LONG(BASE_FIELD, NAME, NAME_STR, NUMBER_TRAITS, CONTAINER)\
      CREATE_IDEAL_NON_ALGEBRICAL(BASE_FIELD, NAME, NAME_STR, NUMBER_TRAITS, CONTAINER)\
      CREATE_EXPANSION_CLASS(BASE_FIELD, MINIMAL_POLYNOM, NAME, NAME_STR, NUMBER_TRAITS, CONTAINER)\
      CREATE_TRAITS_CLASS(BASE_FIELD, NAME, NUMBER_TRAITS, CONTAINER)\
      CREATE_NUMCALC_CLASS(BASE_FIELD, NAME, NUMBER_TRAITS, CONTAINER, MATH::Algebra::Number_traits<NAME>)

/*****************************************************************************/
/**
  * @brief Simple algebrical Extension, with long format
  * @details This macro creates a new algebrical type. You can determine
  *          the used traits class and container
  * @param BASE_FIELD The type of the base field
  * @param MINIMAL_POLYNOM The minimal Polynomial object
  * @param NAME the name of the new type
  * @param NAME_STR the string shape of the new algebrical element
  * @param NUMBER_TRAITS The traits class for BASE_FIELD
  * @param CONTAINER The type of the used container
  */
#define ALGEBRICAL_EXPANSION_LONG(BASE_FIELD, MINIMAL_POLYNOM, NAME, NAME_STR, NUMBER_TRAITS, CONTAINER)\
      CREATE_IDEAL_ALGEBRICAL(BASE_FIELD, MINIMAL_POLYNOM, NAME, NAME_STR, NUMBER_TRAITS, CONTAINER)\
      CREATE_EXPANSION_CLASS(BASE_FIELD, MINIMAL_POLYNOM, NAME, NAME_STR, NUMBER_TRAITS, CONTAINER)\
      CREATE_TRAITS_CLASS(BASE_FIELD, NAME, NUMBER_TRAITS, CONTAINER)\
      CREATE_NUMCALC_CLASS(BASE_FIELD, NAME, NUMBER_TRAITS, CONTAINER, MATH::Algebra::Number_traits<NAME>)

/*****************************************************************************/
/**
  * @brief Creates an ideal for non algebrical field expension.
  * @param BASE_FIELD The type of the base field
  * @param MINIMAL_POLYNOM The minimal Polynomial object
  * @param NAME the name of the new type
  * @param NAME_STR the string shape of the new algebrical element
  * @param NUMBER_TRAITS The traits class for BASE_FIELD
  * @param CONTAINER The type of the used container
  */
#define CREATE_IDEAL_NON_ALGEBRICAL(BASE_FIELD, NAME, NAME_STR, NUMBER_TRAITS, CONTAINER)\
namespace MATH\
{\
  namespace Algebra\
  {\
    namespace Ideals\
    {\
      struct Ideal_##NAME\
      {\
        private:\
          Ideal_##NAME()\
          {}\
\
          Ideal_##NAME(const Ideal_##NAME&)\
          {}\
\
          Ideal_##NAME& operator=(const Ideal_##NAME&)\
          {return *this;}\
        public:\
          static bool isCongruentElement(const BASE_FIELD& a)\
          {  return true;  }\
\
          static void division(const BASE_FIELD& a, \
                               BASE_FIELD& divisior,\
                               BASE_FIELD& rem)\
          {\
            divisior = NUMBER_TRAITS::additiveUnit;\
            rem = a;\
          }\
\
\
          static Polynomial<BASE_FIELD, CONTAINER, NUMBER_TRAITS>* getMinimalPolynomial()\
          {\
            return 0;\
          }\
\
          static std::string strShape;\
      };\
\
\
      std::string Ideal_##NAME::strShape = NAME_STR;\
\
    }\
  }\
}\

/*****************************************************************************/
/**
  * @brief Creates an ideal for algebrical field expension.
  * @param BASE_FIELD The type of the base field
  * @param MINIMAL_POLYNOM The minimal Polynomial object
  * @param NAME the name of the new type
  * @param NAME_STR the string shape of the new algebrical element
  * @param NUMBER_TRAITS The traits class for BASE_FIELD
  * @param CONTAINER The type of the used container
  */
#define CREATE_IDEAL_ALGEBRICAL(BASE_FIELD, MINIMAL_POLYNOM, NAME, NAME_STR, NUMBER_TRAITS, CONTAINER)\
namespace MATH\
{\
  namespace Algebra\
  {\
    namespace Ideals\
    {\
      struct Ideal_##NAME\
      {\
        private:\
          Ideal_##NAME()\
          {}\
\
          Ideal_##NAME(const Ideal_##NAME&)\
          {}\
\
          Ideal_##NAME& operator=(const Ideal_##NAME&)\
          {return *this;}\
        public:\
          static bool isCongruentElement(const BASE_FIELD& a)\
          {  return true;  }\
\
          static void division(const BASE_FIELD& a, \
                               BASE_FIELD& divisior,\
                               BASE_FIELD& rem)\
          {\
            divisior = NUMBER_TRAITS::additiveUnit;\
            rem = a;\
          }\
\
          static Polynomial<BASE_FIELD, CONTAINER, NUMBER_TRAITS> poly;\
\
          static Polynomial<BASE_FIELD, CONTAINER, NUMBER_TRAITS>* getMinimalPolynomial()\
          {\
            return &poly;\
          }\
\
          static std::string strShape;\
      };\
\
\
      std::string Ideal_##NAME::strShape = NAME_STR;\
\
			Polynomial<BASE_FIELD, CONTAINER, NUMBER_TRAITS>\
        Ideal_##NAME::poly = MINIMAL_POLYNOM;\
    }\
  }\
}

/*****************************************************************************/
/**
  * @brief Creates the new class for field expension.
  * @param BASE_FIELD The type of the base field
  * @param MINIMAL_POLYNOM The minimal Polynomial object
  * @param NAME the name of the new type
  * @param NAME_STR the string shape of the new algebrical element
  * @param NUMBER_TRAITS The traits class for BASE_FIELD
  * @param CONTAINER The type of the used container
  */
#define CREATE_EXPANSION_CLASS(BASE_FIELD, MINIMAL_POLYNOM, NAME, NAME_STR, NUMBER_TRAITS, CONTAINER)\
namespace MATH\
{\
  namespace Algebra\
  {\
\
    class NAME\
      :public FieldExpansion<BASE_FIELD,\
                             Ideals::Ideal_##NAME,\
                             CONTAINER,\
                             NUMBER_TRAITS>\
    {\
      typedef typename FieldExpansion<BASE_FIELD,\
                             Ideals::Ideal_##NAME,\
                             CONTAINER,\
                             NUMBER_TRAITS>::IndexType IndexType;\
\
      public:\
        NAME(const BASE_FIELD& number)\
          :FieldExpansion<BASE_FIELD,\
                          Ideals::Ideal_##NAME,\
                          CONTAINER,\
                          NUMBER_TRAITS>(number)\
        {\
          this->correctShape();\
        }\
        NAME(const IdealAdicRepresentation<BASE_FIELD,\
                                           Ideals::Ideal_##NAME,\
                                           CONTAINER,\
                                           NUMBER_TRAITS>& other)\
          :FieldExpansion<BASE_FIELD,\
                          Ideals::Ideal_##NAME,\
                          CONTAINER,\
                          NUMBER_TRAITS>(other)\
        {\
          this->correctShape();\
        }\
\
        template<class T>\
        NAME(IndexType numOfCoeffs, T first, ...)\
        {\
          va_list vlist;\
          va_start(vlist, first);\
          this->constructRepresentation(numOfCoeffs.value, first, vlist);\
        }\
\
        NAME& operator=(const IdealAdicRepresentation<BASE_FIELD,\
                                                      Ideals::Ideal_##NAME,\
                                                      CONTAINER,\
                                                      NUMBER_TRAITS>& other)\
        {\
          IdealAdicRepresentation<BASE_FIELD,\
                                  Ideals::Ideal_##NAME,\
                                  CONTAINER,\
                                  NUMBER_TRAITS>::operator=(other);\
          return *this;\
        }\
    };\
  }\
}

/*****************************************************************************/
/**
  * @brief Create traits class for the new generated field
  * @param BASE_FIELD The base field, what expanded
  * @param NAME Name of the new generated field
  * @param CONTAINER The used container type which can hold BASE_FIELDs
  * @param NUMBER_TRAITS The traits class for BASE_FIELD
  */
#define CREATE_TRAITS_CLASS(BASE_FIELD, NAME, NUMBER_TRAITS, CONTAINER)\
namespace MATH\
{\
  namespace Algebra\
  {\
    template<>\
    class Number_traits<NAME>\
      :public Number_traits<FieldExpansion<BASE_FIELD,\
                                           Ideals::Ideal_##NAME,\
                                           CONTAINER,\
                                           NUMBER_TRAITS> >\
    {\
        static const NAME additiveUnit;\
        static const NAME multiplicativeUnit;\
    };\
    NAME const Number_traits<NAME>::additiveUnit = NUMBER_TRAITS::additiveUnit;\
    NAME const Number_traits<NAME>::multiplicativeUnit = NUMBER_TRAITS::multiplicativeUnit;\
  }\
}\

/*****************************************************************************/
/**
  * @brief Create number calculator class specialization for the new generated field
  * @param BASE_FIELD The base field, what expanded
  * @param NAME Name of the new generated field
  * @param CONTAINER The used container type which can hold BASE_FIELDs
  * @param NUMBER_TRAITS The traits class for BASE_FIELD
  * @param NEW_NUM_TRAITS The generated number traits for the new Type.
  *                       It should be MATH::Algebra::Number_traits<NAME>
  */
#define CREATE_NUMCALC_CLASS(BASE_FIELD, NAME, NUMBER_TRAITS, CONTAINER, NEW_NUM_TRAITS)\
namespace MATH\
{\
  namespace Algebra\
  {\
    template<>\
    struct NumberCalculator<NAME,\
                            NEW_NUM_TRAITS,\
                            true>\
      :NumberCalculator<FieldExpansion<BASE_FIELD,\
                                       Ideals::Ideal_##NAME,\
                                       CONTAINER,\
                                       NUMBER_TRAITS>,\
                        NEW_NUM_TRAITS,\
                        true>\
    {\
    };\
\
    template<>\
    struct NumberCalculator<NAME,\
                            NEW_NUM_TRAITS,\
                            false>\
      :NumberCalculator<FieldExpansion<BASE_FIELD,\
                                       Ideals::Ideal_##NAME,\
                                       CONTAINER,\
                                       NUMBER_TRAITS>,\
                        NEW_NUM_TRAITS,\
                        false>\
    {\
    };\
  }\
}

#endif

