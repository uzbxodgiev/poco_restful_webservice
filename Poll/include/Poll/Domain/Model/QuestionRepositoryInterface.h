/*
 * (C) Copyright 2019 Edson (http://edsonaraujosoares.com) and others.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Contributors:
 *     Edson Araújo Soares
 */

#ifndef Poll_Domain_Model_QuestionRepositoryInterface_INCLUDED
#define Poll_Domain_Model_QuestionRepositoryInterface_INCLUDED

#include <list>
#include <string>
#include "Poll/Domain/Model/Question.h"

namespace Poll {
namespace Domain {
namespace Model {


    class QuestionRepositoryInterface
    {
    public:
        virtual ~QuestionRepositoryInterface() = default;

        /*!
         * It saves a given Question.
         *
         * @param question The question to save.
         */
        virtual void store(const Question &) = 0;

        /*!
         * It updates a given Question data.
         *
         * @param question The question to be updated.
         */
        virtual void update(const Question &) = 0;

        /*!
         * It destroys completely a question and its related data.
         *
         * @param question The Question to be erased.
         */
        virtual void erase(const Question &) = 0;

        /*!
         * It finds a Question using its identity.
         *
         * @param identity The Question's identity.
         * @return The Question, if found. If not, it throws an exception.
         */
        virtual Question withIdentity(const std::string &) = 0;

    };


} } }

#endif
