
var app = function() {
    var self = {};
    self.is_configured = false;

    var server_url = "https://luca-ucsc-teaching-backend.appspot.com/keystore/";
    var call_interval = 2000;
    self.can_show_button = false;
    Vue.config.silent = false; // show all warnings
    self.my_identity = randomString(20);
    self.score_o =0;
    self.score_x =0;
    self.player_x = null;
    self.player_o = null;
    self.new_game = false;
    self.null_board1 = [0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    ];
    self.null_board2 = [0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    ];
    //bindings for the board variables
    var empty = 0;
    var ship  = 1;
    var miss  = 2;
    var hit   = 3;

    function call_server(){
        console.log("calling the server");
        if(self.vue.chosen_magic_word === null){
            console.log("No magic word.");
            setTimeout(call_server, call_interval);
        }else{
            //Now we can do a server call
            var extra_delay = Math.floor(Math.random()*1000);
            console.log("calling ajax");
            $.ajax({
                dataType: 'json',
                url: server_url+ 'read',
                data:{key: self.vue.chosen_magic_word},
                success: self.process_server_data,
                complete: setTimeout(call_server, call_interval + extra_delay)
            });

        }
    }

    self.send_state = function(){
        console.log("sending state");
        $.post(server_url + 'store',
            {
                key: self.vue.chosen_magic_word,
                val: JSON.stringify(
                    {
                        'player_x':self.player_x,
                        'player_o':self.player_o,
                        'board_x' :self.vue.board_x,
                        'board_o' :self.vue.board_o,
                        'new_game':self.new_game
                    }
                )
            }
        );
    };

    self.set_magic_word = function(){
        console.log("setting magic word");

        self.vue.chosen_magic_word = self.vue.magic_word;
        self.vue.need_new_magic_word = false;
        //reset board:
        //TODO: IF IT DOESNT WORK TRY setBoards because the boards need to be filled with ships not blank like tictactoe
        self.vue.board_x = self.null_board1;
        self.vue.board_o = self.null_board2;
        self.vue.is_my_turn = false;
        self.vue.my_role = "";
    };
    function whose_turn(board_x,board_o) {
                num_x = 0;
                num_o = 0;
                for (var i = 0; i < 64; i++) {
                    if (board_x[i] == 2 || board_x[i] == 3) {
                        num_o++;
                    }
                    if (board_o[i] == 2 || board_o[i] == 3) {
                        num_x++;
                    }
                }
                if (num_o >= num_x) {
                    console.log("x's turn"+ num_x);
                    return 'x';
                } else {
                    console.log("o's turn"+ num_o);
                    return 'o';
                }
    };

    self.update_local_vars = function(server_answer){
        console.log("updating local vars");
        //First we need to extract and set our role from the server answer
        console.log("Identity is : "  + self.my_identity);
        if(server_answer.player_o === self.my_identity){
            self.vue.my_role ='o';
        }else if( server_answer.player_x === self.my_identity){
            self.vue.my_role = 'x';
        }else{
            self.vue.my_role = ' ';
        }
        var device_has_newer_state = false;

        var count_x=0;
        var count_o=0;
        var count_x_s=0;
        var count_o_s=0;

        //loop over all of the entries in the board and determine something from the state
        for(var i =0; i< 64; i++){
            //do x first
            var server_x = server_answer.board_x[i];
            var server_o = server_answer.board_o[i];
            var self_x = self.vue.board_x[i];
            var self_o = self.vue.board_o[i];
            //define some counter variables for the board scores
            if(server_x == 3)
                count_x_s++;
            if(server_o == 3)
                count_o_s++;
            if(self_x == 3)
                 count_x++;
            if(self_o == 3)
                 count_o++;



            //TODO:
            //might have to do triple equals here
            if(
                //server has a hit but we do not
                ((server_x == hit) && (self_x != hit))
                //server has a miss but we do not
                ||((server_x == miss) && (self_x != miss))
            )
            {//set the local state to the server boards state:
                Vue.set(self.vue.board_x, i,server_answer.board_x[i]);
            }//we have a hit on a ship but the server does not
            else if(
                ((self_x == hit) && (server_x == ship))//The local board has a hit, and the server does not
                ||((self_x == miss)&&(server_x == empty))//The local board has a miss and the server does not
            ) {
                //set device state flag
                device_has_newer_state = true;
            }

            if(
                //server has a hit but we do not
                ((server_o == hit) && (self_o != hit))
                //server has a miss but we do not
                ||((server_o == miss) && (self_o != miss))
            )
            {//set the local state to the server boards state:
                Vue.set(self.vue.board_o, i,server_answer.board_o[i]);
            }//we have a hit on a ship but the server does not
            else if(
                ((self_o == hit) && (server_o == ship))//The local board has a hit, and the server does not
                ||((self_o == miss)&&(server_o == empty))//The local board has a miss and the server does not
            ) {
                //set device state flag
                device_has_newer_state = true;
            }
        }
        self.vue.is_my_turn = ((self.vue.board_x != null) && (self.vue.board_o !=null))&&
                (self.vue.my_role === whose_turn(self.vue.board_x,self.vue.board_o));
                console.log(whose_turn(self.vue.board_x,self.vue.board_o));
        if(device_has_newer_state){
            self.send_state();
        }

        if(count_o == 10 || count_o_s == 10 || count_x == 10 || count_x_s == 10){
            self.vue.can_show_button = true;

            //alert("Game Finished");
        }else{
            self.vue.can_show_button = false;
        }

    };
    self.process_server_data = function(data){
        //if data is null we send our data
    console.log("in process server data");
        if(!data.result){
            console.log("null data in process server data");
            self.player_x = self.my_identity;
            self.player_o = null;
            //generate the starter state for both players of battleship
            self.vue.setBoards();
            self.vue.is_my_turn = false;
            self.send_state();
        }else{
            self.server_answer = JSON.parse(data.result);
            if(self.server_answer.new_game == true){
                //This code can never run before the x and o are chosen so it is safe to set
                // things here
                //This is where we will update the new game state
                self.new_game = false;
                self.can_show_button = false;
                for(var i = 0; i<64; i++){
                            Vue.set(self.vue.board_o,i,self.server_answer.board_o[i]);
                            Vue.set(self.vue.board_x,i,self.server_answer.board_x[i]);
                };

            }
            self.player_x = self.server_answer.player_x;
            self.player_o = self.server_answer.player_o;
            if(self.player_o === null || self.player_o ===null){
                //one of the above is missign and has not connected yet
                self.vue.is_my_turn = false;
                console.log("not all players present");

                if(self.player_o === self.my_identity || self.player_x === self.my_identity){
                    //we are here so we are good
                    console.log("waiting for other player to join");
                    self.vue.game_status = "Waiting for other player to connect";
                } else{
                    //we must be null ourselves so let us join the game
                    console.log("signing up now.");
                    self.vue.game_status = "Signing up";
                    if(self.player_x === null){
                        //pick x by default
                        self.player_x = self.my_identity;
                        //set the boards here and then define them as the state
                        self.board_x = self.getBoard();
                        self.board_o = self.getBoard();
                        //define the server boards from the instance of the game local to x at first
                        self.send_state();
                    }else if(self.player_o === null){
                        self.player_o = self.my_identity;
                        //set the vue boards from the server answer
                        for(var i = 0; i<64; i++){
                            Vue.set(self.vue.board_o,i,self.server_answer.board_o[i]);
                            Vue.set(self.vue.board_x,i,self.server_answer.board_x[i]);
                        };
                        // self.board_x = self.server_answer.board_x;
                        // self.board_o = self.server_answer.board_o;
                        self.send_state();
                    }else{
                        //the magic word is already taken
                        self.vue.need_new_magic_word = true;
                    }
                }
            }else{
                console.log("Both Players are present");
                self.vue.game_status = "In game with both players";
                //figure out our role
                if(self.server_answer.new_game == true){
                    new_game = false;
                    for(var i = 0; i<64; i++){
                            Vue.set(self.vue.board_o,i,self.server_answer.board_o[i]);
                            Vue.set(self.vue.board_x,i,self.server_answer.board_x[i]);
                        };
                    //updating new games
                    console.log("updating boards because of new game");
                    self.update_local_vars();
                    self.send_state();
                    return;
                }
                if(self.player_o !== self.my_identity && self.player_x !== self.my_identity){
                    //TODO: Add a v-bind here to update the main page with the fact we are trying to enter a third game
                    //since we match neither identity we are intruding on a game
                    self.vue.need_new_magic_word = true;
                    console.log("need new magic word");
                }else{
                    console.log("updating local vars");
                    self.update_local_vars(self.server_answer);
                }
            }
        }
    };

    self.start_new_game = function(){
        //set the new game flag to true and then send it in the server call
       self.new_game = true;

      var board = getBoard();
                //test if Vue can do it's thing out here
                for (var i = 0; i < 64; i++) {
                    Vue.set(self.vue.board_o, i, board[i]);
                }
                board = getBoard();
                for (var i = 0; i < 64; i++) {
                    Vue.set(self.vue.board_x, i, board[i]);
                }

                //hid the button locally
        self.can_show_button = false;
                //send the state
       self.send_state();
       
    };

    self.setBoards = function(){
        var board = getBoard();
                //test if Vue can do it's thing out here
                for (var i = 0; i < 64; i++) {
                    Vue.set(this.board_o, i, board[i]);
                }
                var board = getBoard();
                for (var i = 0; i < 64; i++) {
                    Vue.set(this.board_x, i, board[i]);
                }
    };

    self.shoot_at_o = function (i, j) {
                console.log("clicked at " + i + " " + j);

               if(!self.vue.is_my_turn){
                   console.log("not your turn, current turn is: "+ self.vue.is_my_turn);
                   return;
               }
               //return if the square is already filled
                if (this.board_o[8 * i + j] == 2 || this.board_o[8 * i + j] == 3) {
                    console.log("Unable to click here");
                    return;
                }

                //register a hit on a ship
                if (this.board_o[8 * i + j] == 1) {
                    //set the board spot to 3 for hit
                    console.log("hit at " + i + " " + j);
                    Vue.set(this.board_o, 8 * i + j, 3);
                } else {
                    //set a miss
                    console.log("miss at " +i + " "+j);
                    Vue.set(this.board_o, 8 * i + j, 2);
                }
                //INCREMENT A TURN COUNTER HERE
        self.vue.is_my_turn = false;
               self.send_state();
            };
    self.shoot_at_x = function (i, j) {
                //return if the square is already filled
                //this.setBoards();
                if(!self.vue.is_my_turn){
                   console.log("not your turn, current turn is: "+ self.vue.is_my_turn);
                   return;
               }
                if (this.board_x[8 * i + j] == 2 || this.board_x[8 * i + j] == 3) {
                    alert("failing check for clickiness");
                    return;
                }
                if (this.board_x[8 * i + j] == 1) {
                    //there is a ship here so mark the hit
                    Vue.set(this.board_x, 8 * i + j, 3);
                } else {
                    //set to grey
                    Vue.set(this.board_x, 8 * i + j, 2);
                }
                self.vue.is_my_turn = false;
                self.send_state();
            };

    self.set_new_game = function(){
        if(self.vue.can_show_button == false){
            self.vue.can_show_button = true;
        }else{
            self.vue.can_show_button = false;
        }
    }

    self.vue = new Vue({
        el: '#app',
        data: {
            message: 'GAME OF BATTLESHIPS',
            magic_word: "",
            game_status:"Waiting for magic word to send",
            game_over: false,
            chosen_magic_word: null,
            need_new_magic_word: false,
            my_role: "",
            board_x: self.null_board1,
            board_o: self.null_board2,
            is_other_present: false,
            is_my_turn: false,
            can_start_new_game: self.new_game,
            can_show_button: self.can_show_button
        },

        methods: {

            //Vue.set(target,key,value)
            shoot_at_o: self.shoot_at_o,
            shoot_at_x: self.shoot_at_x,
            setBoards: self.setBoards,
            set_magic_word: self.set_magic_word,
            start_new_game: self.start_new_game,
            set_new_game: self.set_new_game

        }

    });



//hide all of the ship stuff in here...
    function getBoard() {


        function isvalid(board, x, y, orientation, ship_size, board_size) {
            if (orientation) {
                if (x + ship_size >= board_size) return false;
                for (var i = x; i < x + ship_size; i++) {
                    if (board[i][y] != '*' ||
                        (y - 1 >= 0 && board[i][y - 1] != '*') || // to ensure that ships do not "touch each other"
                        (y + 1 < board_size && board[i][y + 1] != '*'))
                        return false;
                }
                if ((x - 1 >= 0 && board[x - 1][y] != '*') ||
                    (x + ship_size < board_size && board[x + ship_size][y] != '*')) return false;
            } else {
                if (y + ship_size >= board_size) return false;
                for (var i = y; i < y + ship_size; i++) {
                    if (board[x][i] != '*' ||
                        (x - 1 >= 0 && board[x - 1][i] != '*') || // to ensure that ships do not "touch each other"
                        (x + 1 < board_size && board[x + 1][i] != '*'))
                        return false;
                }
                if ((y - 1 >= 0 && board[x][y - 1] != '*') ||
                    (y + ship_size < board_size && board[x][y + ship_size] != '*')) return false;
            }
            return true;
        }

        function print(board) {
            var size = Math.sqrt(board.length);
            for (var i = 0; i < size; i++) {
                var s = "";
                for (var j = 0; j < size; j++) {
                    s += board[i * size + j];
                }
                console.log(s);
            }
        }

//creates a ship in board with shipid
        function setShip(board, orientation, x, y, ship_size, shipid) {
            if (orientation) {
                for (var i = x; i < x + ship_size; i++) {
                    board[i][y] = shipid;
                }
            } else {
                for (var i = y; i < y + ship_size; i++) {
                    board[x][i] = shipid;
                }
            }
        }

//get random integers in range [Min, Max]
        function get_random(Min, Max) {
            return Math.floor(Math.random() * (Max - Min + 1)) + Min;
        }

//create a ship
        function createShip(board, board_size, ship_size, shipid) {
            var counter = 0;
            while (counter < 200) {
                counter++;
                var orientation = get_random(0, 1);//0 -> horizontal, 1-> vertical
                var x = 0;
                var y = 0;
                if (orientation) {
                    x = get_random(0, board_size - ship_size - 1);
                    y = get_random(0, board_size - 1);
                } else {
                    x = get_random(0, board_size - 1);
                    y = get_random(0, board_size - ship_size - 1);
                }
                if (!isvalid(board, x, y, orientation, ship_size, board_size)) continue; //check if it conflicts
                setShip(board, orientation, x, y, ship_size, shipid);
                break;
            }
        }

//create all ships
        function createShips(board, board_size) {
            var ships = [[1, 3], [3, 1], [2, 2]]; // first element of every pair is number of ships, second element is length of ship
            var shipid = 1;
            for (var i = 0; i < ships.length; i++) {
                for (var count = 0; count < ships[i][0]; count++) {
                    createShip(board, board_size, ships[i][1], shipid);
                    shipid++;
                }
            }
        }

//flatten 2d vector to 1d vector
        function flatten(board) {
            var size = board.length;
            var board2 = new Array(size * size);
            for (var i = 0; i < size; i++) {
                for (var j = 0; j < size; j++)
                    board2[i * size + j] = board[i][j];
            }
            return board2;
        }

// get 8x8 board flattened
        function getABoard() {
            var size = 8;
            var board = new Array(size);
            for (var i = 0; i < size; i++) {
                board[i] = new Array(size);
                for (var j = 0; j < size; j++)
                    board[i][j] = '*';
            }
            createShips(board, size);
            board = flatten(board);

            for (var i = 0; i < 64; i++) {
                if (board[i] == "*") {
                    board[i] = 0;
                } else {
                    board[i] = 1;
                }
                ;
            }

            return board;
        }

        return getABoard();
    }

    call_server();

    return self;

}

var APP = null;

jQuery(function(){
    APP = app();
    APP.initialize();
});